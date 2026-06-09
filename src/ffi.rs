#[cxx::bridge]

mod ffi {
    struct Vector {
        x: i32,
        y: i32,
    }

    unsafe extern "C++" {
        include!("cpp/physics.h");
        // fn update(delta: f32);
        fn run();
        fn get_positions() -> Vec<Vector>;
    }
}

pub use ffi::*;
