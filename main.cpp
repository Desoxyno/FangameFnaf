#include "scenes/scene_manager.h"
#include <raylib.h>
#include "global_variables.h"


#if DISCORD_ENABLED
    #define DISCORDPP_IMPLEMENTATION
    #include "discordpp.h"
#endif

int main() {
    #if DISCORD_ENABLED
        std::cout << "🚀 Initializing Discord SDK...\n";

        // Create our Discord Client
        auto client = std::make_shared<discordpp::Client>();

        // Set up logging callback
        client->AddLogCallback([](auto message, auto severity) {
        std::cout << "[" << EnumToString(severity) << "] " << message << std::endl;
        }, discordpp::LoggingSeverity::Info);

        // Set up status callback to monitor client connection
        client->SetStatusChangedCallback([client](discordpp::Client::Status status, discordpp::Client::Error error, int32_t errorDetail) {
        std::cout << "🔄 Status changed: " << discordpp::Client::StatusToString(status) << std::endl;

        if (status == discordpp::Client::Status::Ready) {
            std::cout << "✅ Client is ready! You can now call SDK functions.\n";

            // Access initial relationships data
            std::cout << "👥 Friends Count: " << client->GetRelationships().size() << std::endl;

            // Configure rich presence details
            discordpp::Activity activity;
            activity.SetType(discordpp::ActivityTypes::Playing);
            activity.SetState("Playing FangameFnaf");
            activity.SetDetails("In Menu");

            // Update rich presence
            client->UpdateRichPresence(activity, [](discordpp::ClientResult result) {
            if(result.Successful()) {
                std::cout << "🎮 Rich Presence updated successfully!\n";
            } else {
                std::cerr << "❌ Rich Presence update failed";
            }
            });

        } else if (error != discordpp::Client::Error::None) {
            std::cerr << "❌ Connection Error: " << discordpp::Client::ErrorToString(error) << " - Details: " << errorDetail << std::endl;
        }
        });

        // Generate OAuth2 code verifier for authentication
        auto codeVerifier = client->CreateAuthorizationCodeVerifier();

        // Set up authentication arguments
        discordpp::AuthorizationArgs args{};
        args.SetClientId(APPLICATION_ID);
        args.SetScopes(discordpp::Client::GetDefaultPresenceScopes());
        args.SetCodeChallenge(codeVerifier.Challenge());

        // Begin authentication process
        client->Authorize(args, [client, codeVerifier](auto result, auto code, auto redirectUri) {
        if (!result.Successful()) {
            std::cerr << "❌ Authentication Error: " << result.Error() << std::endl;
            return;
        } else {
            std::cout << "✅ Authorization successful! Getting access token...\n";

            // Exchange auth code for access token
            client->GetToken(APPLICATION_ID, code, codeVerifier.Verifier(), redirectUri,
            [client](discordpp::ClientResult result,
            std::string accessToken,
            std::string refreshToken,
            discordpp::AuthorizationTokenType tokenType,
            int32_t expiresIn,
            std::string scope) {
                std::cout << "🔓 Access token received! Establishing connection...\n";
                // Next Step: Update the token and connect
                client->UpdateToken(discordpp::AuthorizationTokenType::Bearer,  accessToken, [client](discordpp::ClientResult result) {
                if(result.Successful()) {
                    std::cout << "🔑 Token updated, connecting to Discord...\n";
                    client->Connect();
                }
                });
            });
        }
        });
    #endif

    InitWindow(1280, 720, "FangameFnaf");
    InitAudioDevice(); 

    SetTraceLogLevel(LOG_WARNING);

    SceneManager manager;

    // Keep application running to allow SDK to receive events and callbacks
    while (!WindowShouldClose()) {
        manager.Tick();
        discordpp::RunCallbacks();
    }

    CloseAudioDevice();

    CloseWindow();

    return 0;
}