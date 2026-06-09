mod display;
mod ffi;
mod logic;
use display::{WindowConfig, run_window};

fn main() {
    println!("Hello, world!");
    let config = WindowConfig {
        title: "Physics Engine",
        width: 1280.0,
        height: 720.0,
        resizable: true,
        decorations: true,
    };

    run_window(config);
}
