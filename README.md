# Simple HTTP Server in C

This is a simple HTTP server written in C that provides basic functionality for handling HTTP requests. It is designed to handle the following features:

- **Echo Route**: Echoes back whatever comes after the "/echo" route in the request.
- **User-Agent Route**: Displays the User-Agent header received from the client.
- **File Serving**: Serves files if requested by the client. If the requested file exists, it is sent to the client; otherwise, a 404 error is returned.
- **Invalid Request Handling**: Responds with a 400 error for invalid requests.

## Prerequisites

- C compiler (e.g., gcc)
- Basic understanding of C programming

## Usage

1. Clone the repository:

   ```bash
   git clone https://github.com/hugo-russeil/http-server.git
   ```

2. Compile the server:

   ```bash
   make
   ```

3. Run the server:

   ```bash
   ./server
   ```

4. Once the server is running, you can send HTTP requests to it using tools like cURL or web browsers.

## Routes

- **Echo Route**: Accessible via `/echo`. Anything after `/echo` in the URL will be echoed back in the server's response.

  Example:
  ```
  GET /echo/hello HTTP/1.1
  Host: localhost:8080
  ```

  Response:
  ```
  hello
  ```

- **User-Agent Route**: Accessible via `/user-agent`. Displays the User-Agent header received from the client.

  Example:
  ```
  GET /user-agent HTTP/1.1
  Host: localhost:8080
  User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:97.0) Gecko/20100101 Firefox/97.0
  ```

  Response:
  ```
  User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:97.0) Gecko/20100101 Firefox/97.0
  ```

- **File Serving**: Any other route will be interpreted as a request for a file. If the requested file exists, it will be sent to the client. Otherwise, a 404 error will be returned.

  Example (assuming `index.html` exists):
  ```
  GET /index.html HTTP/1.1
  Host: localhost:8080
  ```

  Response (if `index.html` exists):
  
  > Content of index.html
  

  Response (if `index.html` does not exist):
  ```
  404 Not Found
  ```

- **Invalid Request Handling**: The server responds with a 400 error for invalid requests.

  ```
  400 Bad Request
  ```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.