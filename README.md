<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <h1>&#128218; Modern Book Manager</h1>
        <p align="center">
            <img src="Captures/1.png" alt="Modern Book Manager Screenshot">
        </p>
        <div class="section">
            <h2>&#128214; Overview</h2>
            <p>A modern, multi-threaded C++ application that fetches book data from the <a href="https://openlibrary.org/developers/api" target="_blank">Open Library API</a>, processes it, and dynamically updates a sleek graphical user interface (GUI).</p>
        </div>
        <div class="section">
            <h2>&#128736; System Architecture</h2>
            <h3>1. Download Thread (Data Retrieval)</h3>
            <p><strong>Purpose:</strong> Fetches JSON data asynchronously from the Open Library API.</p>
            <p align="center">
                <img src="Captures/4.png" alt="Download Thread Process">
            </p>
            <h3>2. Parse Thread (JSON Processing)</h3>
            <p><strong>Purpose:</strong> Extracts meaningful information from JSON responses and structures them for UI presentation.</p>
            <h3>3. UI Thread (Modern GUI Rendering)</h3>
            <p><strong>Purpose:</strong> Updates and manages the interactive graphical user interface (GUI).</p>
            <p align="center">
                <img src="Captures/3.png" alt="UI Screenshot">
            </p>
        </div>
        <div class="section">
            <h2>&#128640; Execution Flow (Main Loop)</h2>
            <ol>
                <li>Initializes shared data structures.</li>
                <li>Spawns and manages worker threads.</li>
                <li>Waits for user input and signals appropriate threads.</li>
                <li>Handles application shutdown gracefully.</li>
            </ol>
        </div>
        <div class="section">
            <h2>&#127912; Modern UI Design</h2>
            <ul>
                <li>Smooth Rounded Corners</li>
                <li>Dark Backgrounds & Highlights</li>
                <li>Custom Loading Animations</li>
            </ul>
        </div>
        <div class="section">
            <h2>&#128295; Core Technologies</h2>
            <ul>
                <li><strong>C++17/20</strong> - Multi-threading & modern paradigms</li>
                <li><strong>httplib</strong> - Lightweight HTTP client</li>
                <li><strong>nlohmann::json</strong> - JSON parsing</li>
                <li><strong>Dear ImGui</strong> - GUI framework</li>
            </ul>
        </div>
        <div class="section">
            <h2>&#128230; How to Build & Run</h2>
            <h3>1. Clone the Repository</h3>
            <pre><code>git clone https://github.com/saeed-asle/bookApp.git
cd bookApp</code></pre>
            <h3>2. Using Visual Studio (Recommended)</h3>
            <ul>
                <li>Open <code>CppApp.sln</code> in Visual Studio.</li>
                <li>Set <code>ConnectedApp</code> as the Startup Project.</li>
                <li>Build and Run (Ctrl + Shift + B, then F5).</li>
            </ul>
            <h3>3. Using CMake (Alternative)</h3>
            <pre><code>mkdir build && cd build
cmake ..
cmake --build .
./ConnectedApp</code></pre>
        </div>
        <div class="section">
            <h2>&#9889; Author</h2>
            <p><strong>Saeed Asle</strong></p>
            <p><a href="https://www.linkedin.com/in/saidasla/" target="_blank">🔗 LinkedIn</a></p>
        </div>
        <div class="section">
            <h2>&#128196; License</h2>
            <p>MIT License - Feel free to use and modify!</p>
        </div>
    </div>
</body>
</html>
