#[cxx::bridge]

mod ffi {
    struct Vector {
        x: f32,
        y: f32,
    }

    unsafe extern "C++" {
        include!("cpp/run.h");
        include!("cpp/physics.h");
        fn init() -> i32;
        fn update();
        fn get_positions() -> Vec<Vector>;
    }
}

pub use ffi::*;
