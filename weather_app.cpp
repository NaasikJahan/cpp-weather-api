#include <iostream>
#include <string>
#include <curl/curl.h>
#include <cstdlib>
#include </workspaces/codespaces-blank/json.hpp>

// For convenience
using json = nlohmann::json;

// Callback function to handle the data fetched by cURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* out) {
    size_t totalSize = size * nmemb;
    out->append((char*)contents, totalSize);
    return totalSize;
}

// Function to fetch weather data from OpenWeatherMap API
std::string fetchWeatherData(const std::string& apiKey, const std::string& city) {
    const std::string baseUrl = "http://api.openweathermap.org/data/2.5/weather?q=";
    const std::string fullUrl = baseUrl + city + "&appid=" + apiKey + "&units=metric";

    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "cURL Error: " << curl_easy_strerror(res) << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    return response;
}

// Function to parse and display weather data
void displayWeatherData(const std::string& data) {
    try {
        auto jsonData = json::parse(data);

        // Check for error in response
        if (jsonData.contains("cod") && jsonData["cod"] != 200) {
            std::cerr << "API Error: " << jsonData.value("message", "Unknown error") << std::endl;
            return;
        }

        // Parse and display weather data
        std::string city = jsonData.value("name", "Unknown location");
        double temperature = jsonData["main"]["temp"];
        temperature = ((temperature * 9)/5) + 32;
        int humidity = jsonData["main"]["humidity"];
        std::string weatherDescription = jsonData["weather"][0]["description"];

        std::cout << "Weather in " << city << ":\n";
        std::cout << "Temperature: "  << std::fixed << std::setprecision(2) << temperature << "°F\n";
        std::cout << "Humidity: " << humidity << "%\n";
        std::cout << "Description: " << weatherDescription << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON data: " << e.what() << std::endl;
    }
}

int main() {
    const char* apiKeyEnv = std::getenv("OPENWEATHER_API_KEY");

    if (apiKeyEnv == nullptr) {
        std::cerr << "Error: OPENWEATHER_API_KEY environment variable is not set.\n";
        return 1;
    }

    std::string apiKey(apiKeyEnv);
    std::string city;

    std::cout << "Enter city name: ";
    std::getline(std::cin, city);

    std::string weatherData = fetchWeatherData(apiKey, city);

    if (!weatherData.empty()) {
        displayWeatherData(weatherData);
    } else {
        std::cerr << "Failed to fetch weather data.\n";
    }

    return 0;
}
