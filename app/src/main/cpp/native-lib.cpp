#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "helloNdk"
#define LOGD(format, ...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, format, ##__VA_ARGS__)
#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, format, ##__VA_ARGS__)
#define LOGI(format, ...)  __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, format, ##__VA_ARGS__)
#define LOGW(format, ...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, format, ##__VA_ARGS__)
//#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
//#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
//#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
//#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("JNI_OnLoad is working");
    JNIEnv *env = nullptr;
    LOGI("打印了日志........");
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    assert(env != nullptr);
    //registerNatives -> env->RegisterNatives
//    if (!registerNatives(env)) {
//        return JNI_ERR;
//    }

    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_grass_hellondk_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    LOGI("stringFromJNI is working");
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_grass_hellondk_MainActivity_sayHello(JNIEnv *env, jobject thiz) {
    // TODO: implement sayHello()
    LOGI("sayHello is working");
    std::string hello = "sayHello() is working2";
    return env->NewStringUTF(hello.c_str());
}

//extern "C"
//JNIEXPORT jobject JNICALL
//Java_com_grass_hellondk_MainActivity_testClass(JNIEnv *env, jobject thiz, jint value) {
//    // TODO: implement testClass()
//    jclass clazz = env->FindClass("java/lang/Integer");
//    if (clazz != nullptr) {
//        jmethodID integerConstructID = env->GetMethodID(clazz, "<init>", "(I)V");
//        return env->NewObject(clazz, integerConstructID, value);
//    }
//    return NULL;
//}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_grass_hellondk_MainActivity_newObj(JNIEnv *env, jobject thiz, jint value) {
    jclass clazz = env->FindClass("java/lang/Integer");
    if (clazz != nullptr) {
        jmethodID integerConstructID = env->GetMethodID(clazz, "<init>", "(I)V");
        return env->NewObject(clazz, integerConstructID, value);
    }
    return NULL;
}