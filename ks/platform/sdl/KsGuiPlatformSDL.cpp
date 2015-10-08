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

#include <ks/gl/KsGLConfig.hpp>

#include <SDL2/SDL.h>

#include <ks/KsTimer.hpp>
#include <ks/gui/KsGuiPlatform.hpp>
#include <ks/shared/KsCallbackTimer.hpp>

namespace ks
{
    namespace gui
    {
        // ============================================================= //
        // ============================================================= //

        class PlatformWindowSDL : public IPlatformWindow
        {
        public:
            PlatformWindowSDL(Window::Attributes& attrs,
                              Window::Properties& props,
                              bool load_gl_fns)
            {
                // set SDL window construction flags
                Uint32 window_flags=0;

                window_flags |= SDL_WINDOW_OPENGL;

                if(attrs.resizable) {
                    window_flags |= SDL_WINDOW_RESIZABLE;
                }
                if(!attrs.decorated) {
                    window_flags |= SDL_WINDOW_BORDERLESS;
                }
                if(props.fullscreen == Window::FullscreenMode::Desktop) {
                    window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
                }
                if(props.fullscreen == Window::FullscreenMode::Display) {
                    window_flags |= SDL_WINDOW_FULLSCREEN;
                }
                // TODO: window focus
                // if(props.focused) {
                //     window_flags |= SDL_WINDOW_INPUT_GRABBED;
                // }
                if(!props.visible) {
                    window_flags |= SDL_WINDOW_HIDDEN;
                }
                // if(props.always_on_top) // I don't think SDL supports this

                // surface
                SDL_GL_ResetAttributes();

                // set requested surface params
                SDL_GL_SetAttribute(SDL_GL_RED_SIZE,attrs.red_bits);
                SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,attrs.green_bits);
                SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,attrs.blue_bits);
                SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,attrs.alpha_bits);
                SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,attrs.depth_bits);
                SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,attrs.stencil_bits);

                if(attrs.samples > 0) {
                    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);
                    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,attrs.samples);
                }

                // set requested context params
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,attrs.version_major);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,attrs.version_minor);

                if(attrs.profile == Window::Attributes::OpenGLProfile::Core) {
                    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                                        SDL_GL_CONTEXT_PROFILE_CORE);
                }

                if(attrs.profile == Window::Attributes::OpenGLProfile::Compatibility) {
                    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                                        SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
                }

                if(attrs.api == Window::Attributes::OpenGLAPI::OpenGLES) {
                    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                                        SDL_GL_CONTEXT_PROFILE_ES);
                }

                if(attrs.forward_compat) {
                    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                                        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
                }

                // create the window and context
                m_window = SDL_CreateWindow(
                            props.title.c_str(),
                            props.x,
                            props.y,
                            props.width,
                            props.height,
                            window_flags);

                if(m_window == nullptr) {
                    std::string const err_msg(SDL_GetError());
                    throw WindowCreationFailed(
                                "SDL: Failed to create window: "+err_msg);
                }

                m_context = SDL_GL_CreateContext(m_window);
                if(m_context == nullptr) {
                    std::string const err_msg(SDL_GetError());
                    throw WindowCreationFailed(
                                "SDL: Failed to create context: "+err_msg);
                }

                // load opengl functions
                // TODO Do we have to load the OpenGL functions
                // for every new context?
                #ifdef KS_ENV_GL_LOAD_FUNCPTRS
                    if(load_gl_fns) {
                        if(!gladLoadGL()) {
                            throw WindowCreationFailed(
                                        "glad: Could not load OpenGL functions");
                        }
                    }
                #endif

                // set the vsync interval
                // TODO: Should this only be called once per
                // per application? Does multiple swap intervals
                // for different contexts in a single application
                // make any sense?
                if(SDL_GL_SetSwapInterval(props.swap_interval) != 0) {
                    std::string const err_msg(SDL_GetError());
                    LOG.Warn() << "SDL: Failed to set swap interval to "
                               << props.swap_interval;

                    LOG.Warn() << "SDL: " << err_msg;
                }

                // save the actual parameters received
                // from the window/context request
                int window_w,window_h;
                SDL_GetWindowSize(m_window,&window_w,&window_h);
                props.width = window_w;
                props.height = window_h;

                int window_x,window_y;
                SDL_GetWindowPosition(m_window,&window_x,&window_y);
                props.x = window_x;
                props.y = window_y;

                window_flags = SDL_GetWindowFlags(m_window);
                attrs.resizable = ((window_flags & SDL_WINDOW_RESIZABLE) == SDL_WINDOW_RESIZABLE);
                attrs.decorated = ((window_flags & SDL_WINDOW_BORDERLESS) == SDL_WINDOW_BORDERLESS) ? false : true;

                if((window_flags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN) {
                    props.fullscreen = Window::FullscreenMode::Display;
                }
                else if((window_flags & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP) {
                    props.fullscreen = Window::FullscreenMode::Desktop;
                }
                else {
                    props.fullscreen = Window::FullscreenMode::None;
                }

                // TODO: window focus
                // props.focused = ((window_flags & SDL_WINDOW_INPUT_FOCUS) == SDL_WINDOW_INPUT_FOCUS);
                props.visible = ((window_flags & SDL_WINDOW_SHOWN) == SDL_WINDOW_SHOWN);

                int gl_attr_red_bits;
                int gl_attr_green_bits;
                int gl_attr_blue_bits;
                int gl_attr_alpha_bits;
                int gl_attr_depth_bits;
                int gl_attr_stencil_bits;
                int gl_attr_samples;
                int gl_attr_profile;
                int gl_attr_version_major;
                int gl_attr_version_minor;
                int gl_attr_flags;

                SDL_ClearError();

                props.visible = SDL_GL_GetSwapInterval();
                SDL_GL_GetAttribute(SDL_GL_RED_SIZE,&gl_attr_red_bits);
                SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE,&gl_attr_green_bits);
                SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE,&gl_attr_blue_bits);
                SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE,&gl_attr_alpha_bits);
                SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE,&gl_attr_depth_bits);
                SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE,&gl_attr_stencil_bits);
                SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES,&gl_attr_samples);
                SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,&gl_attr_profile);
                SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,&gl_attr_version_major);
                SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,&gl_attr_version_minor);
                SDL_GL_GetAttribute(SDL_GL_CONTEXT_FLAGS,&gl_attr_flags);

                std::string const err_msg(SDL_GetError());
                if(!err_msg.empty()) {
                    throw WindowCreationFailed(
                                "SDL: Could not query window/context"+err_msg);
                }

                attrs.red_bits = gl_attr_red_bits;
                attrs.blue_bits = gl_attr_blue_bits;
                attrs.green_bits = gl_attr_green_bits;
                attrs.alpha_bits = gl_attr_alpha_bits;
                attrs.depth_bits = gl_attr_depth_bits;
                attrs.stencil_bits = gl_attr_stencil_bits;
                attrs.samples = gl_attr_samples;

                if(gl_attr_profile == SDL_GL_CONTEXT_PROFILE_ES) {
                    attrs.api = Window::Attributes::OpenGLAPI::OpenGLES;
                    attrs.profile = Window::Attributes::OpenGLProfile::Auto;
                }
                else {
                    attrs.api = Window::Attributes::OpenGLAPI::OpenGL;
                    if(gl_attr_profile == SDL_GL_CONTEXT_PROFILE_CORE) {
                        attrs.profile = Window::Attributes::OpenGLProfile::Core;
                    }
                    else {
                        attrs.profile = Window::Attributes::OpenGLProfile::Compatibility;
                    }
                }

                attrs.version_major = gl_attr_version_major;
                attrs.version_minor = gl_attr_version_minor;
                attrs.forward_compat = ((gl_attr_flags & SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG) ==
                                        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

                // release the context
                this->ReleaseContext();
            }

            ~PlatformWindowSDL()
            {

            }

            bool IsCurrentContext()
            {
                return (SDL_GL_GetCurrentContext() == m_context);
            }

            void MakeContextCurrent()
            {
                if(SDL_GL_GetCurrentContext() == m_context) {
                    return;
                }

                auto err = SDL_GL_MakeCurrent(m_window,m_context);
                if(err != 0) {
                    std::string err_msg(SDL_GetError());
                    throw WindowContextMakeCurrentError(
                                "SDL: MakeCurrent failed: "+err_msg);
                }
            }

            void ReleaseContext()
            {
                auto err = SDL_GL_MakeCurrent(NULL,NULL);
                if(err != 0) {
                    std::string err_msg(SDL_GetError());
                    throw WindowContextMakeCurrentError(
                                "SDL: Release context failed: "+err_msg);
                }
            }

            void SwapBuffers()
            {
                SDL_GL_SwapWindow(m_window);
            }

            void SetSize(Window::Size const &size)
            {
                SDL_SetWindowSize(m_window,size.first,size.second);
                signal_size_changed.Emit(size);
            }

            void SetPosition(Window::Position const &position)
            {
                SDL_SetWindowPosition(m_window,position.first,position.second);
                signal_position_changed.Emit(position);
            }

            void SetFullscreen(Window::FullscreenMode fullscreen)
            {
                Uint32 flags=0;

                if(fullscreen == Window::FullscreenMode::Display) {
                    flags |= SDL_WINDOW_FULLSCREEN;
                }
                else if(fullscreen == Window::FullscreenMode::Desktop) {
                    flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
                }

                int err = SDL_SetWindowFullscreen(m_window,flags);
                if(err != 0) {
                    std::string err_msg(SDL_GetError());
                    throw WindowSettingFailed(
                                "SDL: Failed to set fullscreen mode: "+err_msg);
                }

                signal_fullscreen_changed.Emit(fullscreen);
            }

            void SetFocused(bool)
            {
                // TODO: window focus: Not sure if this option
                // exists in SDL (SetWindowGrab?)
                throw WindowSettingFailed(
                            "SDL: Setting focus unsupported");
            }

            void SetVisible(bool visible)
            {
                if(visible) {
                    SDL_ShowWindow(m_window);
                }
                else {
                    SDL_HideWindow(m_window);
                }

                signal_visible_changed.Emit(visible);
            }

            void SetAlwaysOnTop(bool)
            {
                throw WindowSettingFailed(
                            "SDL: Setting Always On Top unsupported");
            }

            void SetSwapInterval(uint swap_interval)
            {
                if(SDL_GL_SetSwapInterval(swap_interval) != 0) {
                    std::string const err_msg(SDL_GetError());
                    throw WindowSettingFailed(
                                "SDL: Failed to set swap interval: "+err_msg);
                }

                signal_swap_interval_changed.Emit(swap_interval);
            }

            void SetTitle(std::string const &title)
            {
                SDL_SetWindowTitle(m_window,title.c_str());
                signal_title_changed.Emit(title);
            }

            void Destroy()
            {
                SDL_DestroyWindow(m_window);
                SDL_GL_DeleteContext(m_context);
            }

            SDL_Window* GetSDLWindow()
            {
                return m_window;
            }

        private:
            SDL_Window* m_window;
            SDL_GLContext m_context;
        };

        // ============================================================= //
        // ============================================================= //

        // returning 1 adds the event to SDL's event queue
        // returning 0 drops the event so it will not be
        // processed again in ie. Platform::Impl::processEvents
        static int handlePriorityAppEvents(void* userdata, SDL_Event* event)
        {
            IPlatform* platform = static_cast<IPlatform*>(userdata);

            switch (event->type)
            {
                case SDL_APP_TERMINATING: {
                    // Premature termination by OS
                    // TODO: Should we have a separate signal for this?
                    platform->Quit();
                    return 0;
                }
                case SDL_APP_LOWMEMORY: {
                    // Corresponds to:
                    // iOS: didReceiveMemoryWarning
                    // Android: onLowMemory

                    // Low memory warning; The OS is requesting this
                    // application try to free up some memory
                    platform->signal_low_memory.Emit();
                    return 0;
                }
                case SDL_APP_WILLENTERBACKGROUND: {
                    // Corresponds to:
                    // iOS: willResignActive
                    // Android: onPause

                    // May be called when the user suspends the app
                    // or the application is interrupted (ie. phone call)
                    platform->signal_pause.Emit();
                    return 0;
                }
                case SDL_APP_DIDENTERBACKGROUND: {
                    // Corresponds to:
                    // iOS: didEnterBackground

                    // We don't do anything here
                    return 0;
                }
                case SDL_APP_WILLENTERFOREGROUND: {
                    // Corresponds to:
                    // iOS: willEnterForeground

                    // We don't do anything here
                    return 0;
                }
                case SDL_APP_DIDENTERFOREGROUND: {
                    // Corresponds to:
                    // iOS: didBecomeActive
                    // Android: onResume

                    // Called when the application is resumed and active
                    platform->signal_resume.Emit();
                    return 0;
                }
                default: {
                    // No special processing, add it to the event queue
                    return 1;
                }
            }
        }

        // ============================================================= //
        // ============================================================= //

        class PlatformSDL : public IPlatform
        {
        public:
            PlatformSDL(shared_ptr<EventLoop> event_loop) :
                m_event_loop(event_loop),
                m_loaded_gl_funcs(false)
            {
                m_evproc_timer =
                        make_object<CallbackTimer>(
                            m_event_loop,
                            std::chrono::milliseconds(17),
                            [this](){ this->processEvents(); });

                // Init sdl
                if(SDL_Init(SDL_INIT_VIDEO) < 0) {
                    std::string error_msg(SDL_GetError());
                    throw PlatformInitFailed("Unable to initialize SDL: "+error_msg);
                }

                // Enumerate display screens
                enumerateScreens();

                // Install event filter for priority app events
                SDL_SetEventFilter(handlePriorityAppEvents,this);
            }

            ~PlatformSDL()
            {

            }

            void Run()
            {
                LOG.Trace() << "PlatformSDL::Run";
                m_evproc_timer->Start();
                m_event_loop->Run();
                LOG.Trace() << "PlatformSDL::Run returned";
            }

            void Quit()
            {
                LOG.Trace() << "PlatformSDL::Quit";

                // Immediately stop all system event processing
                m_evproc_timer->Stop();
                m_event_loop->PostStopEvent();
            }

            std::vector<shared_ptr<Screen const>> GetScreens()
            {
                std::vector<shared_ptr<Screen const>> list_screens;
                for(auto& screen : m_list_screens) {
                    list_screens.push_back(screen);
                }

                return list_screens;
            }

            shared_ptr<IPlatformWindow>
            CreateWindow(Window::Attributes& win_attrs,
                         Window::Properties& win_props)
            {
                // Request that GL functions be loaded if required
                bool load_gl_fns = !m_loaded_gl_funcs;

                m_list_windows.push_back(
                            make_shared<PlatformWindowSDL>(
                                win_attrs,
                                win_props,
                                load_gl_fns));

                if(!m_loaded_gl_funcs) {
                    m_loaded_gl_funcs = true;
                }

                return m_list_windows.back();
            }

            void DestroyWindow(shared_ptr<IPlatformWindow> rem_window)
            {
                auto it =
                        std::find_if(
                            m_list_windows.begin(),
                            m_list_windows.end(),
                            [rem_window](shared_ptr<PlatformWindowSDL> const &window) {
                                return (window == rem_window);
                            });

                if(it != m_list_windows.end()) {
                    (*it)->Destroy();
                    m_list_windows.erase(it);
                }
            }

        private:
            void enumerateScreens()
            {
                // Enumerate display screens
                int screen_count = SDL_GetNumVideoDisplays();
                if(screen_count <= 0) {
                    std::string const err_msg(SDL_GetError());
                    throw PlatformInitFailed(
                                "SDL: Failed to get num displays: "+err_msg);
                }

                for(int i=0; i < screen_count; i++) {
                    // name
                    const char* name = SDL_GetDisplayName(i);
                    if(name==nullptr) {
                        std::string const err_msg(SDL_GetError());
                        throw PlatformInitFailed("SDL: Failed to query displays: "+err_msg);
                    }

                    // dimensions
                    SDL_Rect size_px_rect;
                    if(SDL_GetDisplayBounds(i,&size_px_rect) < 0) {
                        std::string const err_msg(SDL_GetError());
                        throw PlatformInitFailed("SDL: Failed to query displays: "+err_msg);
                    }

                    // dpi
                    float ddpi,hdpi,vdpi;
                    if(SDL_GetDisplayDPI(i,&ddpi,&hdpi,&vdpi) < 0) {
                        std::string const err_msg(SDL_GetError());
                        throw PlatformInitFailed("SDL: Failed to query displays: "+err_msg);
                    }

                    // orientation
                    // The orientation is just a guess based on the
                    // current screen dimensions
                    Screen::Orientation orientation =
                            Screen::Orientation::Landscape;

                    if(size_px_rect.h > size_px_rect.w) {
                        orientation = Screen::Orientation::Portrait;
                    }

                    uint height_mm = (size_px_rect.h/hdpi)*2.54*10;
                    uint width_mm = (size_px_rect.w/hdpi)*2.54*10;

                    m_list_screens.push_back(
                                make_shared<Screen>(
                                    std::string(name),
                                    orientation,
                                    std::pair<uint,uint>(size_px_rect.w,size_px_rect.h),
                                    std::pair<uint,uint>(height_mm,width_mm),
                                    ddpi));
                }
            }

            void processEvents()
            {
                // Get all available sdl events
                SDL_Event sdl_event;
                std::vector<SDL_Event> list_sdl_events;
                while(SDL_PollEvent(&sdl_event) != 0) {
                    list_sdl_events.push_back(sdl_event);
                }

                // TODO: merge redundant sdl events

                // Process SDL events
                bool keep_processing = true;
                for(auto &sdl_ev : list_sdl_events)
                {
                    switch(sdl_ev.type)
                    {
                        case SDL_QUIT: {
                            LOG.Trace() << "SDL_QUIT";
                            // TODO call SDL_Quit?
                            keep_processing = false;
                            signal_quit.Emit();
                            //this->Quit();
                            break;
                        }
                        case SDL_WINDOWEVENT: {
                            // Get the window this event is from
                            auto sdl_win_id = sdl_ev.window.windowID;
                            auto window = *getWindowFromSDLId(sdl_win_id);

                            switch(sdl_ev.window.event)
                            {
                                case SDL_WINDOWEVENT_RESIZED: {

                                    // TODO: This might indicate that the
                                    // orientation of the display has changed;
                                    // need to check!

                                    window->signal_size_changed.Emit(
                                                Window::Size(
                                                    sdl_ev.window.data1,
                                                    sdl_ev.window.data2));
                                    break;
                                }
                                case SDL_WINDOWEVENT_CLOSE: {
                                    LOG.Trace() << "SDL_WINDOW_CLOSE";
                                    window->signal_close.Emit();
                                }

                                default: {
                                    break;
                                }
                            }

                            break;
                        }
                        case SDL_RENDER_DEVICE_RESET: {
                            // an indication that the opengl context
                            // has been destroyed and recreated; may
                            // happen when android apps are backgrounded
                            // or windows are resized/fullscreened

                            // a recreated context means all buffers,
                            // textures and other data associated with
                            // the context have been destroyed and must
                            // be recreated/reset
                            LOG.Trace() << "SDL_RENDER_DEVICE_RESET";
                            signal_graphics_reset.Emit();
                            break;
                        }
                        default: {
                            break;
                        }
                    }

                    if(!keep_processing) {
                        break;
                    }
                }
            }

            std::vector<shared_ptr<PlatformWindowSDL>>::iterator
            getWindowFromSDLId(Id sdl_win_id)
            {
                auto it =
                        std::find_if(
                            m_list_windows.begin(),
                            m_list_windows.end(),
                            [sdl_win_id](shared_ptr<PlatformWindowSDL> const &window) {
                                return (window->GetSDLWindow() == SDL_GetWindowFromID(sdl_win_id));
                            });
                return it;
            }

            shared_ptr<EventLoop> m_event_loop;
            shared_ptr<CallbackTimer> m_evproc_timer;
            std::vector<shared_ptr<gui::Screen>> m_list_screens;
            std::vector<shared_ptr<PlatformWindowSDL>> m_list_windows;

            // * flag to indicate whether or not OpenGL
            //   functions have been loaded (may not be
            //   required for certain platforms)
            // * we only load functions once even across
            //   multiple contexts; we assume that only
            //   a single type of context and surface will
            //   be used across all windows
            bool m_loaded_gl_funcs;
        };

        // ============================================================= //
        // ============================================================= //

        shared_ptr<IPlatform> CreatePlatform(shared_ptr<EventLoop> app_event_loop)
        {
            return make_shared<PlatformSDL>(app_event_loop);
        }

        // ============================================================= //
        // ============================================================= //
    }
}