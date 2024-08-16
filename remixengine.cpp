#include <SDL2/SDL.h>
#include <Metal/Metal.h>

class GameEngine {
public:
    void Init();
    void Run();
    void Shutdown();

private:
    void ProcessInput();
    void Update();
    void Render();

    SDL_Window* window;
    SDL_Renderer* renderer;
    id<MTLDevice> device;
    id<MTLCommandQueue> commandQueue;
};

void GameEngine::Init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("Q* Optimized Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    device = MTLCreateSystemDefaultDevice();
    commandQueue = [device newCommandQueue];
}

void GameEngine::Run() {
    bool isRunning = true;
    while (isRunning) {
        ProcessInput();
        Update();
        Render();
        SDL_Delay(16); // Cap frame rate at ~60 FPS
    }
    Shutdown();
}

void GameEngine::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // Handle other input events here
    }
}

void GameEngine::Update() {
    // Game logic and physics updates go here
}

void GameEngine::Render() {
    id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
    // Metal rendering commands go here
    [commandBuffer commit];
}

void GameEngine::Shutdown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
