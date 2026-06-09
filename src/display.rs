use crate::ffi;

use winit::{
    application::ApplicationHandler,
    dpi::LogicalSize,
    event::WindowEvent,
    event_loop::{ActiveEventLoop, ControlFlow, EventLoop},
    window::{Window, WindowId},
};

pub struct WindowConfig {
    pub title: &'static str,
    pub width: f64,
    pub height: f64,
    pub resizable: bool,
    pub decorations: bool,
}

impl Default for WindowConfig {
    fn default() -> Self {
        Self {
            title: "Physics simulation",
            width: 800.0,
            height: 600.0,
            resizable: true,
            decorations: true,
        }
    }
}

pub struct App {
    pub window: Option<Window>,
    pub config: WindowConfig,
}

impl App {
    pub fn new(config: WindowConfig) -> Self {
        Self {
            window: None,
            config,
        }
    }
}

impl ApplicationHandler for App {
    fn resumed(&mut self, event_loop: &ActiveEventLoop) {
        let attrs = Window::default_attributes()
            .with_title(self.config.title)
            .with_inner_size(LogicalSize::new(self.config.width, self.config.height))
            .with_resizable(self.config.resizable)
            .with_decorations(self.config.decorations);

        self.window = Some(event_loop.create_window(attrs).unwrap());
    }

    fn window_event(&mut self, event_loop: &ActiveEventLoop, _id: WindowId, event: WindowEvent) {
        match event {
            WindowEvent::CloseRequested => {
                event_loop.exit();
            }
            WindowEvent::RedrawRequested => {
                if let Some(window) = &self.window {
                    // Put your rendering logic here
                    window.request_redraw();
                }
            }
            WindowEvent::Resized(new_size) => {
                println!("Window resized to {:?}", new_size);
                // Update your renderer here if needed
            }
            _ => {}
        }
    }
}

pub fn run_window(config: WindowConfig) {
    let event_loop = EventLoop::new().unwrap();
    event_loop.set_control_flow(ControlFlow::Poll);

    let mut app = App::new(config);
    event_loop.run_app(&mut app).unwrap();
}
