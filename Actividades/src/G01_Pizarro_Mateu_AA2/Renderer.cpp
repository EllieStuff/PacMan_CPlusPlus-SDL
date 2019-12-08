#include "Renderer.h"

Renderer::Renderer()
{
	// --- INIT ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	m_window = SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	//Initialize renderer color
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	//Initialize PNG loading
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_imageinit";

	// ---- TTF ----
	if (TTF_Init() != 0) throw"No es pot inicialitzar SDL_ttf";

	// ---- AUDIO ----
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags)&mixFlags)) throw "No es pot inicialitzar SDL_mixer";

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) { //Freq��ncia, format, canals, chunksize
		throw "Unable to initialize SDL_mixer audio systems";
	}
};


Renderer::~Renderer()
{
	for (auto &t : m_textureData) SDL_DestroyTexture(t.second), t.second = nullptr;
	for (auto &f : m_fontData) TTF_CloseFont(f.second), f.second = nullptr;
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

};

void Renderer::Clear() { SDL_RenderClear(m_renderer); };

void Renderer::Render() { SDL_RenderPresent(m_renderer); };

void Renderer::LoadFont(Font font) {
	TTF_Font *ttfFont{ TTF_OpenFont(font.path.c_str(), font.size) };
	if (ttfFont == nullptr) throw"No espot inicialitzar TTF_Font";


	m_fontData[font.id] = ttfFont;
};

void Renderer::LoadTexture(const std::string &id, const std::string &path) {
	SDL_Texture *texture{ IMG_LoadTexture(m_renderer, path.c_str()) };
	if (texture == nullptr) throw "No s'han pogut crear les textures";
	m_textureData[id] = texture;
};

void Renderer::LoadTextureText(const std::string &fontId, Text text) {
	SDL_Surface	*tmpSurf = TTF_RenderText_Blended(m_fontData[fontId], text.text.c_str(), SDL_Color{ static_cast<Uint8>(text.color.r), 
		static_cast<Uint8>(text.color.g), static_cast<Uint8>(text.color.b), static_cast<Uint8>(text.color.a) });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";

	SDL_Texture *texture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	m_textureData[text.id] = texture;

};

//
//GetTextureSize

Vector2 Renderer::GetTextureSize(const std::string &id) {
	int w; int h;
	SDL_QueryTexture(m_textureData[id], NULL, NULL, &w, &h);
	return { w, h };
};

void Renderer::PushImage(const std::string &id, const SDL_Rect &rect) {
	SDL_RenderCopy(m_renderer, m_textureData[id], nullptr, &rect);
};

void Renderer::PushSprite(const std::string &id, const SDL_Rect &rectSprite, const SDL_Rect &rectPos) {
	SDL_RenderCopy(m_renderer, m_textureData[id], &rectSprite, &rectPos);
}

void Renderer::PushRotatedSprite(const std::string & id, const SDL_Rect & rectSprite, const SDL_Rect & rectPos, float angle) {
	SDL_Point center = { rectPos.w / 2, rectPos.h / 2 };
	SDL_RenderCopyEx(m_renderer, m_textureData[id], &rectSprite, &rectPos, angle, &center, SDL_FLIP_NONE);
}

void Renderer::SetRendreDrawColor(int r, int g, int b)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
}




Renderer* Renderer::renderer = nullptr;
