#pragma once

#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p) {delete p; p = nullptr;}

// 클래스를 싱글톤으로 생성한다.
// #define DECLARE_SINGLE(c) \
