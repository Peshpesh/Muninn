#include "CText.h"

std::vector<TTF_Font*> CText::FontList;

bool CText::OnInit() {
  TTF_Font* f = NULL;

  if ((f = TTF_OpenFont("msgothic.ttc", HUGE_SIZE)) == NULL) return false;
  FontList.push_back(f);

  if ((f = TTF_OpenFont("msgothic.ttc", LORGE_SIZE)) == NULL) return false;
  FontList.push_back(f);

  if ((f = TTF_OpenFont("msgothic.ttc", MID_SIZE)) == NULL) return false;
  FontList.push_back(f);

  if ((f = TTF_OpenFont("msgothic.ttc", SMOL_SIZE)) == NULL) return false;
  FontList.push_back(f);

  if ((f = TTF_OpenFont("msgothic.ttc", TINY_SIZE)) == NULL) return false;
  FontList.push_back(f);


  if ((f = TTF_OpenFont("GOTHIC.ttf", HUGE_SIZE)) == NULL) return false;
  FontList.push_back(f);

  if ((f = TTF_OpenFont("GOTHIC.ttf", LORGE_SIZE)) == NULL) return false;
  FontList.push_back(f);

  if ((f = TTF_OpenFont("GOTHIC.ttf", MID_SIZE)) == NULL) return false;
  FontList.push_back(f);

  if ((f = TTF_OpenFont("GOTHIC.ttf", SMOL_SIZE)) == NULL) return false;
  FontList.push_back(f);

  if ((f = TTF_OpenFont("GOTHIC.ttf", TINY_SIZE)) == NULL) return false;
  FontList.push_back(f);

  return true;
}

TTF_Font* CText::getFont(const short& ID) {
  if (ID < 0 || ID >= FontList.size()) {
    CError::handler.ReportErr("CText: Bad fontID requested.");
    return NULL;
  }
  return FontList[ID];
}

SDL_Texture* CText::drawText(const short& ID, char const* text, const SDL_Color& c, SDL_Rect* textureR) {
  if (text[0] == '\0') return NULL;

  TTF_Font* font = getFont(ID);
  if (font == NULL) return NULL;

  SDL_Texture* texture = NULL;
  SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text, c);
  if (surf) {
    texture = SDL_CreateTextureFromSurface(CSurface::getRenderer(), surf);
    SDL_FreeSurface(surf);
    if (texture) {
      if (textureR) SDL_QueryTexture(texture, NULL, NULL, &textureR->w, &textureR->h);
    } else {
      CError::handler.ReportErr("CText: Failed to make texture.");
    }
  } else {
    CError::handler.ReportErr("CText: Failed to make surface.");
  }

  return texture;
}

SDL_Texture* CText::drawItalicText(const short& ID, char const* text, const SDL_Color& c, SDL_Rect* textureR) {
  if (text[0] == '\0') return NULL;

  TTF_Font* font = getFont(ID);
  if (font == NULL) return NULL;

  TTF_SetFontStyle(font, TTF_STYLE_ITALIC);

  SDL_Texture* texture = NULL;
  SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text, c);
  if (surf) {
    texture = SDL_CreateTextureFromSurface(CSurface::getRenderer(), surf);
    SDL_FreeSurface(surf);
    if (texture) {
      if (textureR) SDL_QueryTexture(texture, NULL, NULL, &textureR->w, &textureR->h);
    } else {
      CError::handler.ReportErr("CText: Failed to make texture.");
    }
  } else {
    CError::handler.ReportErr("CText: Failed to make surface.");
  }

  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

  return texture;
}

int CText::getLineH(const short& ID) {
  TTF_Font* font = getFont(ID);
  if (font == NULL) return 0;
  return TTF_FontLineSkip(font);
}

void CText::OnCleanup() {
  for (int i = FontList.size() - 1; i >= 0; i++) {
    TTF_CloseFont(FontList[i]);
    FontList[i] = NULL;
  }
  FontList.clear();
}
