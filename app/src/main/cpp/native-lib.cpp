#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_grass_hellondk_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_grass_hellondk_MainActivity_sayHello(JNIEnv *env, jobject thiz) {
    // TODO: implement sayHello()
    std::string hello = "sayHello() is working";
    return env->NewStringUTF(hello.c_str());
}