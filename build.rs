fn main() {
    cxx_build::bridge("src/ffi.rs")
        .file("cpp/main.cpp")
        .file("cpp/physics.cpp")
        .include(".")
        .std("c++17")
        .compile("core");

    println!("cargo:rerun-if-changed=cpp/physics.cpp");
    println!("cargo:rerun-if-changed=cpp/main.cpp");
}
