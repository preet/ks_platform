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

#ifndef KS_PLATFORM_MAIN_HPP
#define KS_PLATFORM_MAIN_HPP

#include <ks/platform/KsPlatformOpts.hpp>

#if defined(KS_ENV_ANDROID) && defined(KS_ENV_SDL2)
    #include <SDL2/SDL_main.h>
#endif

#endif // KS_PLATFORM_MAIN_HPP
