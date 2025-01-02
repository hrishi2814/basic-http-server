
# Simple HTTP Server in C++

This project is a basic implementation of a web server written in **C++** using **sockets**. It demonstrates the process of handling incoming HTTP requests, parsing them, and serving static files from the server's file system. This project is designed to help understand the fundamentals of socket programming, HTTP request parsing, and server-client communication.

---

## Getting Started

### Prerequisites

Make sure you have the following installed on your system:

- **C++ Compiler** (e.g., `g++` for Linux or MinGW for Windows)
- **POSIX-compliant Operating System** (Linux, macOS, or WSL on Windows)

### Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/simple-http-server.git
    cd simple-http-server
    ```

2. Compile the code:
    ```bash
    g++ -o server server.cpp -std=c++11
    ```

3. Run the server:
    ```bash
    ./server
    ```

    The server will start listening on port `4561` by default. You can change this by modifying the port number in the code.

---

## Usage

After starting the server, you can test it by opening a web browser or using **`curl`**:

1. To test a simple **GET** request:
    ```bash
    curl http://localhost:4561/index.html
    ```

2. To test a non-existent file (404 error):
    ```bash
    curl http://localhost:4561/nonexistent.html
    ```

3. The server will return the requested HTML file, or a `404 Not Found` error if the file doesn't exist.

---

## Technologies Used

- **C++**: The core language for this project.
- **Regex (std::regex)**: Used for parsing the HTTP request line.
- **Sockets (sys/socket.h)**: For creating the server and handling client connections.

