#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "helloNdk"
#define LOGD(format, ...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, format, ##__VA_ARGS__)
#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, format, ##__VA_ARGS__)
#define LOGI(format, ...)  __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, format, ##__VA_ARGS__)
#define LOGW(format, ...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, format, ##__VA_ARGS__)


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

extern "C"
JNIEXPORT void JNICALL
Java_com_grass_hellondk_MainActivity_c_1call_1java(JNIEnv *env, jobject thiz) {
    // TODO: implement c_call_java()
    jclass clazz = env->FindClass("com/grass/hellondk/MainActivity");
    if (clazz != nullptr) {
        //Access object field
        jfieldID ageID = env->GetFieldID(clazz, "age", "I");
        jint ageInt = (jint) env->GetIntField(thiz, ageID);

        //Access object method
        jmethodID getAgeID = env->GetMethodID(clazz, "getAge", "(Ljava/lang/String;)Ljava/lang/String;");
        jstring nameStr = env->NewStringUTF("JNI");
        jstring msgStr = (jstring) env->CallObjectMethod(thiz, getAgeID, nameStr);

        //Use string, convert jstring to char sequence
        char *name = (char *) env->GetStringUTFChars(nameStr, NULL);
        char *msg = (char *) env->GetStringUTFChars(msgStr, NULL);
        LOGI("[c_call_java] message:%s; age:%d", msg, ageInt);

        env->ReleaseStringUTFChars(nameStr, name);
        env->ReleaseStringUTFChars(msgStr, msg);
    }
    env->DeleteLocalRef(clazz);
}

// 测试动态注册函数
jint native_text(JNIEnv *env, jobject thiz, jstring message) {
    const char *p_msg = env->GetStringUTFChars(message, JNI_FALSE);
    LOGI("method = %s, msg = %s", __FUNCTION__, p_msg);
    return 0;
}

// 测试动态注册函数
jint native_static_text(JNIEnv *env, jobject thiz, jstring message) {
    const char *p_msg = env->GetStringUTFChars(message, JNI_FALSE);
    LOGI("method = %s, msg = %s", __FUNCTION__, p_msg);
    return 0;
}


static void native_text_array(JNIEnv *env, jobject jobject1, jintArray array) {

    //获取数组长度
    jsize length = env->GetArrayLength(array);
    //获取本地数组
    jint *native_intaray = env->GetIntArrayElements(array, NULL);
    //操作本地数组
    for(int i=0;i<length;i++){
        native_intaray[i]+=100;
    }
    //释放本地数组
    env->ReleaseIntArrayElements(array,native_intaray,0);
}

/*
 * 要注册的函数列表
 * 参数：
 * 1.java中用native关键字声明的函数名
 * 2.函数签名，格式：(参数类型)返回类型, 可以使用javap -s xx.class查看
 * 3.C/C++中对应函数的函数名（地址）
 * */
static const JNINativeMethod nativeMethods[] = {
        {"text",        "(Ljava/lang/String;)I", (void *) native_text},
        {"static_text", "(Ljava/lang/String;)I", (void *) native_static_text},
        {"textArray", "([I)V", (void *) native_text_array}
};

static int registerNatives(JNIEnv *env) {
    //要注册的java类的路径(完整的包名和类名)
    const char *className = "com/grass/hellondk/MainActivity";
    jclass clazz = nullptr;
    clazz = env->FindClass(className);
    if (clazz == nullptr) {
        return JNI_FALSE;
    }
    int methodsCount = sizeof(nativeMethods) / sizeof(nativeMethods[0]);
    //注册函数 参数：java类名， 要注册的函数数组 ，要注册函数的数量
    if (env->RegisterNatives(clazz, nativeMethods, methodsCount) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("JNI_OnLoad is working");
    JNIEnv *env = nullptr;
    LOGI("打印了日志........");
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    assert(env != nullptr);
    if (!registerNatives(env)) {
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}


