/*
   Copyright (C) 2015 Preet Desai (preet.desai@gmail.com)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef KS_GUI_CONVERT_SDL_INPUTS_HPP
#define KS_GUI_CONVERT_SDL_INPUTS_HPP


#include <unordered_map>
#include <SDL2/SDL.h>
#include <ks/gui/KsGuiInput.hpp>
#include <ks/KsLog.hpp>

namespace ks
{
    namespace gui
    {
        namespace
        {
            std::unordered_map<
                SDL_Keycode,
                KeyEvent::Key
            > const keymap_sdl_ks = {
                {SDLK_UNKNOWN, KeyEvent::Key::KEY_UNKNOWN},

                {SDLK_SPACE, KeyEvent::Key::KEY_SPACE},
                {SDLK_QUOTEDBL, KeyEvent::Key::KEY_APOSTROPHE},
                {SDLK_COMMA, KeyEvent::Key::KEY_COMMA},
                {SDLK_MINUS, KeyEvent::Key::KEY_MINUS},
                {SDLK_PERIOD, KeyEvent::Key::KEY_PERIOD},
                {SDLK_SLASH, KeyEvent::Key::KEY_SLASH},
                {SDLK_0, KeyEvent::Key::KEY_0},
                {SDLK_1, KeyEvent::Key::KEY_1},
                {SDLK_2, KeyEvent::Key::KEY_2},
                {SDLK_3, KeyEvent::Key::KEY_3},
                {SDLK_4, KeyEvent::Key::KEY_4},
                {SDLK_5, KeyEvent::Key::KEY_5},
                {SDLK_6, KeyEvent::Key::KEY_6},
                {SDLK_7, KeyEvent::Key::KEY_7},
                {SDLK_8, KeyEvent::Key::KEY_8},
                {SDLK_9, KeyEvent::Key::KEY_9},
                {SDLK_SEMICOLON, KeyEvent::Key::KEY_SEMICOLON},
                {SDLK_EQUALS, KeyEvent::Key::KEY_EQUAL},
                {SDLK_a, KeyEvent::Key::KEY_A},
                {SDLK_b, KeyEvent::Key::KEY_B},
                {SDLK_c, KeyEvent::Key::KEY_C},
                {SDLK_d, KeyEvent::Key::KEY_D},
                {SDLK_e, KeyEvent::Key::KEY_E},
                {SDLK_f, KeyEvent::Key::KEY_F},
                {SDLK_g, KeyEvent::Key::KEY_G},
                {SDLK_h, KeyEvent::Key::KEY_H},
                {SDLK_i, KeyEvent::Key::KEY_I},
                {SDLK_j, KeyEvent::Key::KEY_J},
                {SDLK_k, KeyEvent::Key::KEY_K},
                {SDLK_l, KeyEvent::Key::KEY_L},
                {SDLK_m, KeyEvent::Key::KEY_M},
                {SDLK_n, KeyEvent::Key::KEY_N},
                {SDLK_o, KeyEvent::Key::KEY_O},
                {SDLK_p, KeyEvent::Key::KEY_P},
                {SDLK_q, KeyEvent::Key::KEY_Q},
                {SDLK_r, KeyEvent::Key::KEY_R},
                {SDLK_s, KeyEvent::Key::KEY_S},
                {SDLK_t, KeyEvent::Key::KEY_T},
                {SDLK_u, KeyEvent::Key::KEY_U},
                {SDLK_v, KeyEvent::Key::KEY_V},
                {SDLK_w, KeyEvent::Key::KEY_W},
                {SDLK_x, KeyEvent::Key::KEY_X},
                {SDLK_y, KeyEvent::Key::KEY_Y},
                {SDLK_z, KeyEvent::Key::KEY_Z},
                {SDLK_LEFTBRACKET, KeyEvent::Key::KEY_LEFT_BRACKET},
                {SDLK_BACKSLASH, KeyEvent::Key::KEY_BACKSLASH},
                {SDLK_RIGHTBRACKET, KeyEvent::Key::KEY_RIGHT_BRACKET},
                {SDLK_BACKQUOTE, KeyEvent::Key::KEY_GRAVE_ACCENT},

                {SDLK_ESCAPE, KeyEvent::Key::KEY_ESCAPE},
                {SDLK_RETURN, KeyEvent::Key::KEY_ENTER},
                {SDLK_TAB, KeyEvent::Key::KEY_TAB},
                {SDLK_BACKSPACE, KeyEvent::Key::KEY_BACKSPACE},
                {SDLK_INSERT, KeyEvent::Key::KEY_INSERT},
                {SDLK_DELETE, KeyEvent::Key::KEY_DELETE},
                {SDLK_RIGHT, KeyEvent::Key::KEY_RIGHT},
                {SDLK_LEFT, KeyEvent::Key::KEY_LEFT},
                {SDLK_DOWN, KeyEvent::Key::KEY_DOWN},
                {SDLK_UP, KeyEvent::Key::KEY_UP},
                {SDLK_PAGEUP, KeyEvent::Key::KEY_PAGE_UP},
                {SDLK_PAGEDOWN, KeyEvent::Key::KEY_PAGE_DOWN},
                {SDLK_HOME, KeyEvent::Key::KEY_HOME},
                {SDLK_END, KeyEvent::Key::KEY_END},
                {SDLK_CAPSLOCK, KeyEvent::Key::KEY_CAPS_LOCK},
                {SDLK_SCROLLLOCK, KeyEvent::Key::KEY_SCROLL_LOCK},
                {SDLK_NUMLOCKCLEAR, KeyEvent::Key::KEY_NUM_LOCK},
                {SDLK_PRINTSCREEN, KeyEvent::Key::KEY_PRINT_SCREEN},
                {SDLK_PAUSE, KeyEvent::Key::KEY_PAUSE},
                {SDLK_F1, KeyEvent::Key::KEY_F1},
                {SDLK_F2, KeyEvent::Key::KEY_F2},
                {SDLK_F3, KeyEvent::Key::KEY_F3},
                {SDLK_F4, KeyEvent::Key::KEY_F4},
                {SDLK_F5, KeyEvent::Key::KEY_F5},
                {SDLK_F6, KeyEvent::Key::KEY_F6},
                {SDLK_F7, KeyEvent::Key::KEY_F7},
                {SDLK_F8, KeyEvent::Key::KEY_F8},
                {SDLK_F9, KeyEvent::Key::KEY_F9},
                {SDLK_F10, KeyEvent::Key::KEY_F10},
                {SDLK_F11, KeyEvent::Key::KEY_F11},
                {SDLK_F12, KeyEvent::Key::KEY_F12},
                {SDLK_F13, KeyEvent::Key::KEY_F13},
                {SDLK_F14, KeyEvent::Key::KEY_F14},
                {SDLK_F15, KeyEvent::Key::KEY_F15},
                {SDLK_F16, KeyEvent::Key::KEY_F16},
                {SDLK_F17, KeyEvent::Key::KEY_F17},
                {SDLK_F18, KeyEvent::Key::KEY_F18},
                {SDLK_F19, KeyEvent::Key::KEY_F19},
                {SDLK_F20, KeyEvent::Key::KEY_F20},
                {SDLK_F21, KeyEvent::Key::KEY_F21},
                {SDLK_F22, KeyEvent::Key::KEY_F22},
                {SDLK_F23, KeyEvent::Key::KEY_F23},
                {SDLK_F24, KeyEvent::Key::KEY_F24},
                {SDLK_KP_0, KeyEvent::Key::KEY_KP_0},
                {SDLK_KP_1, KeyEvent::Key::KEY_KP_1},
                {SDLK_KP_2, KeyEvent::Key::KEY_KP_2},
                {SDLK_KP_3, KeyEvent::Key::KEY_KP_3},
                {SDLK_KP_4, KeyEvent::Key::KEY_KP_4},
                {SDLK_KP_5, KeyEvent::Key::KEY_KP_5},
                {SDLK_KP_6, KeyEvent::Key::KEY_KP_6},
                {SDLK_KP_7, KeyEvent::Key::KEY_KP_7},
                {SDLK_KP_8, KeyEvent::Key::KEY_KP_8},
                {SDLK_KP_9, KeyEvent::Key::KEY_KP_9},
                {SDLK_KP_DECIMAL, KeyEvent::Key::KEY_KP_DECIMAL},
                {SDLK_KP_DIVIDE, KeyEvent::Key::KEY_KP_DIVIDE},
                {SDLK_KP_MULTIPLY, KeyEvent::Key::KEY_KP_MULTIPLY},
                {SDLK_KP_MINUS, KeyEvent::Key::KEY_KP_SUBTRACT},
                {SDLK_KP_PLUS, KeyEvent::Key::KEY_KP_ADD},
                {SDLK_KP_ENTER, KeyEvent::Key::KEY_KP_ENTER},
                {SDLK_KP_EQUALS, KeyEvent::Key::KEY_KP_EQUAL},
                {SDLK_LSHIFT, KeyEvent::Key::KEY_LEFT_SHIFT},
                {SDLK_LCTRL, KeyEvent::Key::KEY_LEFT_CONTROL},
                {SDLK_LALT, KeyEvent::Key::KEY_LEFT_ALT},
                {SDLK_LGUI, KeyEvent::Key::KEY_LEFT_SUPER},
                {SDLK_RSHIFT, KeyEvent::Key::KEY_RIGHT_SHIFT},
                {SDLK_RCTRL, KeyEvent::Key::KEY_RIGHT_CONTROL},
                {SDLK_RALT, KeyEvent::Key::KEY_RIGHT_ALT},
                {SDLK_RGUI, KeyEvent::Key::KEY_RIGHT_SUPER},
                {SDLK_MENU, KeyEvent::Key::KEY_MENU}
            };

            KeyEvent ConvertSDLKeyEvent(
                    SDL_KeyboardEvent const &sdl_event)
            {
                KeyEvent ks_event;

                // Action
                ks_event.action =
                        (sdl_event.type == SDL_KEYDOWN) ?
                            KeyEvent::Action::Press :
                            KeyEvent::Action::Release;

                if(sdl_event.repeat)
                {
                    ks_event.action = KeyEvent::Action::Repeat;
                }

                // Scan code
                ks_event.scancode =
                        static_cast<uint>(sdl_event.keysym.scancode);

                // Modifiers
                ks_event.mods = KeyEvent::MOD_NONE;

                if(sdl_event.keysym.mod & KMOD_CTRL)
                {
                    ks_event.mods |= KeyEvent::MOD_CTRL;
                }

                if(sdl_event.keysym.mod & KMOD_SHIFT)
                {
                    ks_event.mods |= KeyEvent::MOD_SHIFT;
                }

                if(sdl_event.keysym.mod & KMOD_ALT)
                {
                    ks_event.mods |= KeyEvent::MOD_ALT;
                }

                if(sdl_event.keysym.mod & KMOD_GUI)
                {
                    ks_event.mods |= KeyEvent::MOD_SUPER;
                }

                // Key
                auto key_it = keymap_sdl_ks.find(sdl_event.keysym.sym);
                if(key_it == keymap_sdl_ks.end())
                {
                    ks_event.key = KeyEvent::Key::KEY_UNKNOWN;
                }
                else
                {
                    ks_event.key = key_it->second;
                }

                return ks_event;
            }
        }

        TouchEvent ConvertSDLTouchFingerEvent(
                SDL_TouchFingerEvent const &sdl_event,
                TimePoint const &timepoint,
                float active_win_width,
                float active_win_height)
        {
            TouchEvent ks_event;
            ks_event.timestamp = timepoint;

            // Action
            if(sdl_event.type == SDL_FINGERMOTION)
            {
                ks_event.action = TouchEvent::Action::None;
            }
            else if(sdl_event.type == SDL_FINGERDOWN)
            {
                ks_event.action = TouchEvent::Action::Press;
            }
            else if(sdl_event.type == SDL_FINGERUP)
            {
                ks_event.action = TouchEvent::Action::Release;
            }

            ks_event.index = sdl_event.fingerId;
            ks_event.x = sdl_event.x*active_win_width;
            ks_event.y = sdl_event.y*active_win_height;

            return ks_event;
        }

        MouseEvent ConverSDLMouseButtonEvent(
                SDL_MouseButtonEvent const &sdl_event,
                TimePoint const &timepoint)
        {
            MouseEvent ks_event;
            ks_event.timestamp = timepoint;

            // Action
            ks_event.action =
                    (sdl_event.type == SDL_MOUSEBUTTONDOWN) ?
                        MouseEvent::Action::Press :
                        MouseEvent::Action::Release;

            // Button
            if(sdl_event.button == SDL_BUTTON_LEFT)
            {
                ks_event.button = MouseEvent::Button::Left;
            }
            else if(sdl_event.button == SDL_BUTTON_RIGHT)
            {
                ks_event.button = MouseEvent::Button::Right;
            }
            else if(sdl_event.button == SDL_BUTTON_MIDDLE)
            {
                ks_event.button = MouseEvent::Button::Middle;
            }

            // Position
            ks_event.x = sdl_event.x;
            ks_event.y = sdl_event.y;

            return ks_event;
        }

        MouseEvent ConvertSDLMouseMotionEvent(
                SDL_MouseMotionEvent const &sdl_event,
                TimePoint const &timepoint)
        {
            MouseEvent ks_event;
            ks_event.timestamp = timepoint;

            // Action
            ks_event.action = MouseEvent::Action::None;

            // Button
            if(sdl_event.state & SDL_BUTTON_LMASK)
            {
                ks_event.button = MouseEvent::Button::Left;
            }
            else if(sdl_event.state == SDL_BUTTON_RMASK)
            {
                ks_event.button = MouseEvent::Button::Right;
            }
            else if(sdl_event.state == SDL_BUTTON_MMASK)
            {
                ks_event.button = MouseEvent::Button::Middle;
            }
            else
            {
                ks_event.button = MouseEvent::Button::None;
            }

            // Position
            ks_event.x = sdl_event.x;
            ks_event.y = sdl_event.y;

            return ks_event;
        }

        ScrollEvent ConvertSDLScrollEvent(
                SDL_MouseWheelEvent const &sdl_event)
        {
            ScrollEvent ks_event;

            ks_event.x = sdl_event.x;
            ks_event.y = sdl_event.y;

            return ks_event;
        }
    }
}

#endif // KS_GUI_CONVERT_SDL_INPUTS_HPP


