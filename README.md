# C++ Weather API

A command-line weather application written in C++ that retrieves and displays current weather data for a user-provided city using the OpenWeather API.

## Features

- Fetches real-time weather data from the OpenWeather REST API
- Sends HTTP requests using libcurl
- Parses JSON responses using nlohmann/json
- Displays temperature, humidity, and weather conditions
- Handles API and JSON parsing errors
- Stores the API key securely using an environment variable instead of hard-coding credentials

## Technologies

- C++
- libcurl
- nlohmann/json
- OpenWeather API
- REST APIs

## Setup

Set your OpenWeather API key as an environment variable:

```bash
export OPENWEATHER_API_KEY="your_api_key_here"
```

Compile the application:

```bash
g++ weather_app.cpp -lcurl -o weather_app
```

Run it:

```bash
./weather_app
```

## Example

```text
Enter city name: Seattle

Weather in Seattle:
Temperature: 62.4 F
Humidity: 71%
Description: overcast clouds
```

## Future Improvements

- Add automated unit and integration tests
- Add CMake build configuration
- Add CI/CD with GitHub Actions
