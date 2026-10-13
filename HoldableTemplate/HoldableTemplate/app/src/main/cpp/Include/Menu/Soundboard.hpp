#pragma once
#include <jni.h>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <mutex>
#include <string>
#include <vector>

// TvMenu soundboard: automatic local playback on button press.
// Playback is local to the headset; this class does not inject audio into Photon Voice.
class Soundboard {
public:
    static inline JavaVM* vm = nullptr;
    static inline jobject player = nullptr;
    static inline std::mutex mutex;
    static inline const std::filesystem::path folder =
        "/sdcard/Android/data/com.Tvmods.Baboon/files/ModFolder/Soundboard";
    static void SetVM(JavaVM* value) { vm = value; }
    static JNIEnv* Env(bool& attached) {
        attached = false; if (!vm) return nullptr;
        JNIEnv* e = nullptr; jint s = vm->GetEnv(reinterpret_cast<void**>(&e), JNI_VERSION_1_6);
        if (s == JNI_EDETACHED) { if (vm->AttachCurrentThread(&e, nullptr) != JNI_OK) return nullptr; attached = true; }
        else if (s != JNI_OK) return nullptr;
        return e;
    }
    static void ClearException(JNIEnv* e) { if (e && e->ExceptionCheck()) e->ExceptionClear(); }
    static bool Supported(const std::filesystem::path& p) {
        std::string x = p.extension().string();
        std::transform(x.begin(), x.end(), x.begin(), [](unsigned char c){ return (char)std::tolower(c); });
        return x==".mp3" || x==".wav" || x==".ogg" || x==".m4a" || x==".aac" || x==".3gp";
    }
    static std::vector<std::filesystem::path> Refresh() {
        std::vector<std::filesystem::path> out; std::error_code ec;
        std::filesystem::create_directories(folder, ec); if (ec) return out;
        for (std::filesystem::directory_iterator i(folder, ec), end; !ec && i!=end; i.increment(ec)) {
            std::error_code e; if (i->is_regular_file(e) && !e && Supported(i->path())) out.push_back(i->path());
        }
        std::sort(out.begin(), out.end()); return out;
    }
    static void Stop() {
        std::lock_guard<std::mutex> guard(mutex); bool attached=false; JNIEnv* e=Env(attached); if (!e) return;
        if (player) {
            jclass c=e->GetObjectClass(player); jmethodID stop=c?e->GetMethodID(c,"stop","()V"):nullptr;
            jmethodID release=c?e->GetMethodID(c,"release","()V"):nullptr;
            if (stop) e->CallVoidMethod(player,stop); ClearException(e);
            if (release) e->CallVoidMethod(player,release); ClearException(e);
            e->DeleteGlobalRef(player); player=nullptr; if(c)e->DeleteLocalRef(c);
        }
        if(attached) vm->DetachCurrentThread();
    }
    static bool Play(const std::string& path) {
        if (!Supported(path)) return false; std::error_code ec;
        if (!std::filesystem::is_regular_file(path,ec) || ec) return false;
        Stop(); std::lock_guard<std::mutex> guard(mutex); bool attached=false; JNIEnv* e=Env(attached); if(!e)return false;
        bool ok=false; jclass c=e->FindClass("android/media/MediaPlayer");
        if (!c) { ClearException(e); if(attached)vm->DetachCurrentThread(); return false; }
        jmethodID ctor=e->GetMethodID(c,"<init>","()V");
        jmethodID set=e->GetMethodID(c,"setDataSource","(Ljava/lang/String;)V");
        jmethodID prep=e->GetMethodID(c,"prepare","()V"); jmethodID start=e->GetMethodID(c,"start","()V");
        jobject p=ctor?e->NewObject(c,ctor):nullptr;
        if(p && set && prep && start) {
            jstring jpath=e->NewStringUTF(path.c_str()); e->CallVoidMethod(p,set,jpath); e->DeleteLocalRef(jpath);
            if(!e->ExceptionCheck())e->CallVoidMethod(p,prep); if(!e->ExceptionCheck())e->CallVoidMethod(p,start);
            if(!e->ExceptionCheck()){player=e->NewGlobalRef(p);ok=player!=nullptr;}
        }
        ClearException(e); if(p)e->DeleteLocalRef(p);e->DeleteLocalRef(c);if(attached)vm->DetachCurrentThread();return ok;
    }
};
