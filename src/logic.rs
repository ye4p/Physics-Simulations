use std::{Instant, thread, time::Duration};

fn convert(old: &Vec<ffi::Vector>) -> Vec<[f32; 2]> {
    let mut v: Vec<[f32; 2]> = Vec::with_capacity(vec.size());
    for i in &old {
        v.push([old[i].x, old[i].y]);
    }
    return v;
}

fn run() {
    let dt: f32 = ffi::init() * 1000;
    let interval = Duration::from_millis(dt as u64);

    let mut next_time = Instant::now() + interval;

    loop {
        ffi::update();
        let pos: Vec<[f32; 2]> = convert(ffi::get_positions());
        // display...

        // sleep until next
        let now = Instant::now();
        if now < next_time {
            sleep(next_time - now);
        }
        next_time += interval;
    }
}

pub use logic::*;
