#pragma once
#include <atomic>
#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>

struct BookInfo {
    std::string title;
    std::string author;
    std::string publish_date;
    std::string description;
    std::vector<std::string> authors;
    std::vector<std::string> genres;
    std::vector<std::string> editions;
    std::string cover_id;  
    int number_of_pages = 0; 
    std::vector<std::string> publishers; 
    std::string isbn_10;  
    std::string isbn_13;
    std::string first_sentence;  
};

struct AuthorInfo {
    std::string name;
    std::string birth_date;
    std::string death_date;
    std::vector<std::string> works;
    std::vector<std::string> alternate_names;
    std::string biography; 
    std::string author_id; 
    std::string top_work;   
    int work_count = 0;   
    std::vector<std::string> top_subjects; 
};

struct SearchResult {
    std::string title;
    std::string author;
    std::string key;
    int edition_count = 0;
    std::vector<std::string> languages;
    std::string first_publish_year;
};

struct BookAPIResult {
    std::string title;
    std::string author;
    std::string publish_date;
    std::string cover_id;
    int number_of_pages = 0;
    std::vector<std::string> publishers;
    std::vector<std::string> identifiers;
    std::string isbn_10;
    std::string isbn_13;
};

struct RecentChange {
    std::string id;
    std::string kind;
    std::string author;
    std::string ip;
    std::string timestamp;
    std::string comment;
    struct ChangeData {
        std::string master;
        std::vector<std::string> duplicates;
    } data;
    struct ChangeDetail {
        std::string key;
        int revision;
    };
    std::vector<ChangeDetail> changes;
};

struct CommonObjects {
    std::atomic_bool exit_flag = false;
    std::atomic_bool start_download = false;
    std::atomic_bool data_ready = false;
    std::atomic_bool json_ready = false;
    std::string url;
    std::string query_type;
    std::string raw_json_data; 
    std::vector<BookInfo> books;
    std::vector<SearchResult> search_results;
    std::vector<RecentChange> recent_changes;
    AuthorInfo author_details;
    BookAPIResult book_details;
    std::mutex data_mutex;
    std::condition_variable cv;
    std::string error_message; 

};
