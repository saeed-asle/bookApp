#include "ParseThread.h"
#include "nlohmann/json.hpp"

void ParseThread::operator()(CommonObjects& common) {
    while (!common.exit_flag) {
        std::unique_lock<std::mutex> lock(common.data_mutex);
        common.cv.wait(lock, [&] { return common.data_ready || common.exit_flag; });
        if (common.exit_flag) break;
        if (!common.error_message.empty()) {
            std::cerr << "[ERROR] Skipping parsing due to previous error: " << common.error_message << std::endl;
            common.data_ready = false;  
            common.json_ready = true;
            common.cv.notify_one();
            continue;
        }
        try {
            auto json_result = nlohmann::json::parse(common.raw_json_data);
            std::cerr << json_result.dump(4) << std::endl;
            common.books.clear();
            common.search_results.clear();
            common.author_details = AuthorInfo();
            common.book_details = BookAPIResult();
            common.recent_changes.clear();
            if (common.query_type == "search") {
                for (const auto& doc : json_result["docs"]) {
                    SearchResult result;
                    result.title = doc.value("title", "No Title");
                    if (doc.contains("author_name") && doc["author_name"].is_array() && !doc["author_name"].empty()) {
                        result.author = doc["author_name"][0];
                    }
                    else {
                        result.author = "Unknown Author";
                    }
                    result.key = doc.value("key", "");
                    common.search_results.push_back(result);
                }
            }
            else if (common.query_type == "work") {
                BookInfo book;
                book.title = json_result.value("title", "No Title");
                if (json_result.contains("authors") && json_result["authors"].is_array() && !json_result["authors"].empty()) {
                    book.author = json_result["authors"][0].contains("author") ? json_result["authors"][0]["author"].value("key", "Unknown Author") : "Unknown Author";
                }
                else {
                    book.author = "Unknown Author";
                }
                book.publish_date = json_result.contains("created") && json_result["created"].is_object()
                    ? json_result["created"].value("value", "Unknown Date")
                    : "Unknown Date";
                if (json_result.contains("covers") && json_result["covers"].is_array() && !json_result["covers"].empty()) {
                    book.cover_id = std::to_string(json_result["covers"][0].get<int>());
                }
                else {
                    book.cover_id = "No Cover ID";
                }
                book.number_of_pages = json_result.value("number_of_pages", 0);
                if (json_result.contains("publishers") && json_result["publishers"].is_array() && !json_result["publishers"].empty()) {
                    for (const auto& publisher : json_result["publishers"]) {
                        book.publishers.push_back(publisher.get<std::string>());
                    }
                }
                else {
                    book.publishers.push_back("Unknown Publisher");
                }
                if (json_result.contains("identifiers")) {
                    if (json_result["identifiers"].contains("isbn_10")) {
                        book.isbn_10 = json_result["identifiers"]["isbn_10"].get<std::string>();
                    }
                    if (json_result["identifiers"].contains("isbn_13")) {
                        book.isbn_13 = json_result["identifiers"]["isbn_13"].get<std::string>();
                    }
                }
                book.description = json_result.value("description", "No description available.");
                common.books.push_back(book);
            }
            else if (common.query_type == "author") {
                common.author_details.name = json_result.value("name", "Unknown Author");
                common.author_details.birth_date = json_result.value("birth_date", "Unknown");
                common.author_details.death_date = json_result.value("death_date", "Unknown");
                common.author_details.author_id = json_result.value("key", "Unknown Author ID");
                common.author_details.top_work = json_result.value("top_work", "Unknown Work");
                common.author_details.work_count = json_result.value("work_count", 0);
                common.author_details.biography = json_result.value("bio", "Biography not available.");
                if (json_result.contains("top_subjects") && json_result["top_subjects"].is_array()) {
                    for (const auto& subject : json_result["top_subjects"]) {
                        common.author_details.top_subjects.push_back(subject.get<std::string>());
                    }
                }
                if (json_result.contains("works") && json_result["works"].is_array()) {
                    for (const auto& work : json_result["works"]) {
                        common.author_details.works.push_back(work.value("title", "Unknown Work"));
                    }
                }
            }
            else if (common.query_type == "book") {
                BookInfo book;
                book.title = json_result.value("title", "No Title");
                if (json_result.contains("authors") && json_result["authors"].is_array() && !json_result["authors"].empty()) {
                    auto first_author = json_result["authors"][0];
                    book.author = first_author.contains("key") ? first_author["key"].get<std::string>() : "Unknown Author";
                }
                else {
                    book.author = "Unknown Author";
                }
                book.publish_date = json_result.value("publish_date", "Unknown Date");
                if (json_result.contains("covers") && json_result["covers"].is_array() && !json_result["covers"].empty()) {
                    book.cover_id = std::to_string(json_result["covers"][0].get<int>());
                }
                else {
                    book.cover_id = "No Cover ID";
                }
                book.number_of_pages = json_result.value("number_of_pages", 0);
                if (json_result.contains("publishers") && json_result["publishers"].is_array()) {
                    for (const auto& publisher : json_result["publishers"]) {
                        book.publishers.push_back(publisher.get<std::string>());
                    }
                }
                else {
                    book.publishers.push_back("Unknown Publisher");
                }
                if (json_result.contains("isbn_10") && json_result["isbn_10"].is_array()) {
                    book.isbn_10 = json_result["isbn_10"][0].get<std::string>();
                }
                if (json_result.contains("isbn_13") && json_result["isbn_13"].is_array()) {
                    book.isbn_13 = json_result["isbn_13"][0].get<std::string>();
                }
                if (json_result.contains("first_sentence") && json_result["first_sentence"].is_object()) {
                    book.description = json_result["first_sentence"].value("value", "No description available.");
                }
                else {
                    book.description = "No description available.";
                }
                common.books.push_back(book);
            }


            else if (common.query_type == "recent_changes") {
                for (const auto& change : json_result) {
                    RecentChange rc;

                    rc.id = change.value("id", "Unknown ID");
                    rc.kind = change.value("kind", "Unknown Kind");
                    if (change.contains("author") && change["author"].is_object()) {
                        std::string author_key = change["author"].value("key", "Unknown Author");
                        if (author_key.find("/people/") == 0) {
                            rc.author = author_key.substr(8);
                        }
                        else {
                            rc.author = "Unknown Author";
                        }
                    }
                    else {
                        rc.author = "Unknown Author";
                    }
                    if (change.contains("ip") && change["ip"].is_null()) {
                        rc.ip = "Unknown IP";
                    }
                    else {
                        rc.ip = change.value("ip", "Unknown IP");
                    }

                    rc.timestamp = change.value("timestamp", "Unknown Time");
                    rc.comment = change.value("comment", "No Comment");
                    if (change.contains("data") && change["data"].is_object()) {
                        rc.data.master = change["data"].value("master", "Unknown Master");

                        if (change["data"].contains("duplicates") && change["data"]["duplicates"].is_array()) {
                            for (const auto& duplicate : change["data"]["duplicates"]) {
                                rc.data.duplicates.push_back(duplicate.get<std::string>());
                            }
                        }
                    }
                    if (change.contains("changes") && change["changes"].is_array()) {
                        for (const auto& change_detail : change["changes"]) {
                            RecentChange::ChangeDetail detail;
                            detail.key = change_detail.value("key", "Unknown Key");
                            detail.revision = change_detail.value("revision", 0);
                            rc.changes.push_back(detail);
                        }
                    }
                    common.recent_changes.push_back(rc);
                }
            }
            common.json_ready = true;
            common.data_ready = false;

            common.cv.notify_one();
        }
        catch (const nlohmann::json::exception& e) {
            std::cerr << "[ERROR] JSON Parsing Error: " << e.what() << std::endl;
            common.error_message = "JSON Parsing Error: " + std::string(e.what());  // Store error
            common.start_download = false;
            common.data_ready = false; 
        }
    }

    
}
