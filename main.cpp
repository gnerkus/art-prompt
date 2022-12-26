
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

int main()
{
    bool quit = false;
    std::vector<std::string> emojiPaths;
    const std::filesystem::path emojis{ "../images/Emoji" };
    for (const auto& entry : std::filesystem::directory_iterator{ emojis })
    {
        emojiPaths.push_back(entry.path());
    }

    std::random_device dev;
    std::mt19937 randomness_generator(dev());
    std::uniform_int_distribution<std::size_t> index_distribution(
        0, emojiPaths.size());

    auto i = index_distribution(randomness_generator);
    const std::string randomEmoji = emojiPaths[i];

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error initializing SDL." << std::endl;
        return 1;
    }

    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);

    int windowWidth = mode.w;
    int windowHeight = mode.h;

    SDL_Window* window = SDL_CreateWindow(
        "Art Prompt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight, SDL_WINDOW_ALWAYS_ON_TOP);

    if (!window)
    {
        std::cout << "Error creating SDL window." << std::endl;
        return 1;
    }

    // -1 means 'default option'
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        std::cout << "Error creating SDL renderer." << std::endl;
        return 1;
    }

    // SDL_Surface* image = IMG_Load(randomEmoji.c_str());
    // SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

    const std::string svg =
        "<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 36 36' "
        "height='512' width='512'><path fill='#E6E7E8' d='M32 32c0 2.209-1.791 "
        "4-4 4H8c-2.209 0-4-1.791-4-4V4c0-2.209 1.791-4 4-4h20c2.209 0 4 1.791 "
        "4 4v28z'/><path fill='#DD2E44' d='M11 7c-2.519 0-4.583 1.87-4.929 "
        "4.293C6.802 10.503 7.839 10 9 10c2.209 0 4 1.791 4 4 0 2 1.497 "
        "2.198.707 2.929C16.13 16.583 16 14.519 16 "
        "12c0-2.761-2.239-5-5-5z'/><path fill='#55ACEE' d='M23 14c0-2.209 "
        "1.791-4 4-4 1.161 0 2.198.503 2.929 1.293C29.583 8.87 27.52 7 25 "
        "7c-2.762 0-5 2.239-5 5 0 2.519-.131 4.583 2.293 4.929C21.503 16.198 "
        "23 16 23 14z'/><path fill='#FFAC33' d='M14 12c0-4.971 4-9 4-9s4 4.029 "
        "4 9-1.791 9-4 9-4-4.029-4-9z'/><path fill='#553788' d='M11.707 "
        "21.071C12.497 21.802 13 22.839 13 24c0 2.209-1.791 4-4 4-1.161 "
        "0-2.198-.503-2.929-1.293C6.417 29.131 8.481 31 11 31c2.761 0 5-2.238 "
        "5-5 0-2.52-1.87-4.583-4.293-4.929zM27 28c-2.209 0-4-1.791-4-4 "
        "0-1.161.503-2.198 1.293-2.929C21.869 21.417 20 23.48 20 26c0 2.762 "
        "2.238 5 5 5 2.52 0 4.583-1.869 4.929-4.293C29.198 27.497 28.161 28 27 "
        "28z'/><path fill='#9266CC' d='M14 24c0 4.971 3 9 4 9s4-4.029 "
        "4-9c0-.874-.055-1.719-.159-2.519C21.357 17.737 19.82 15 18 15c-1.82 "
        "0-3.357 2.737-3.841 6.481-.104.8-.159 1.645-.159 2.519z'/><path "
        "fill='#EDBB9F' d='M13 17c0-3.866 3-4 5-4s5 .134 5 4c0 3.865-2.238 7-5 "
        "7-2.761 0-5-3.135-5-7z'/><circle fill='#662113' cx='16' cy='17' "
        "r='1'/><circle fill='#662113' cx='20' cy='17' r='1'/><path "
        "fill='#662113' d='M18 22c1.104 0 2-.896 2-2h-4c0 1.104.896 2 2 "
        "2z'/><circle fill='#A0041E' cx='6' cy='11' r='1'/><circle fill='#269' "
        "cx='30' cy='11' r='1'/><circle fill='#DD2E44' cx='18' cy='3' "
        "r='1'/></svg>";

    SDL_RWops* rw = SDL_RWFromConstMem(svg.c_str(), svg.size());
    SDL_Surface* image = IMG_LoadSVG_RW(rw);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_Event sdlEvent;
    // sdlEvent is passed by reference
    // event is fetched from queue and assigned to sdlEvent
    while (!quit)
    {
        while (SDL_PollEvent(&sdlEvent))
        {
            // handle core SDL events (close window, key pressed etc.)
            switch (sdlEvent.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quit = true;
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_Rect dstRect = { (mode.w / 2) - 256, (mode.h / 2) - 256, 512, 512 };
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
