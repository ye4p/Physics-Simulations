#[cxx::bridge]

mod ffi {
    unsafe extern "C++" {
        include!("cpp/physics.h");
        // fn update(delta: f32);
        // fn get_positions() -> Vec<f32>;
    }
}

pub use ffi::*;
