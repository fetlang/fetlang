#![crate_type = "staticlib"]
use std::fs;
use std::ffi::CStr;
use std::os::raw::c_char;
use std::path::Path;
use std::io;

#[no_mangle]
pub extern fn rs_touch_file(cpath: *const c_char) -> i32 {
	let mut spath = String::new();
	unsafe{
		spath.push_str(&CStr::from_ptr(cpath).to_string_lossy().into_owned());
	}


	let path = Path::new(".").join(spath);
	let return_value: i32;
	match raw_touch(&path){
		Ok(_) => return_value = 0,
		Err(_) => return_value = -8,
	}
	return return_value;
		
		
}

fn raw_touch(path: &Path) -> io::Result<()> {
	println!("starting raw_touch");
    match fs::OpenOptions::new().create(true).write(true).open(path) {
        Ok(_) => Ok(()),
        Err(e) => Err(e),
    }
}

/*
#[no_mangle]
pub extern fn main() {
/
	println!("Hello!");
	raw_touch(&Path::new("ice.cube"));
	rs_touch_file(CString::new("terminator.x").unwrap());
}
*/
