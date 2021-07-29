//
// Created by Marc Rousavy on 12.07.21.
//

#include "JMediaPlayerData.h"

#include <jni.h>
#include <fbjni/fbjni.h>

#include <memory>
#include <string>

namespace expo {

using namespace facebook;
using namespace jni;

using TSelf = local_ref<HybridClass<expo::JMediaPlayerData>::jhybriddata>;

TSelf JMediaPlayerData::initHybrid(alias_ref<HybridClass::jhybridobject> jThis) {
    return makeCxxInstance(jThis);
}

void JMediaPlayerData::registerNatives() {
    registerHybrid({
       makeNativeMethod("initHybrid", JMediaPlayerData::initHybrid),
       makeNativeMethod("sampleBufferCallback", JMediaPlayerData::sampleBufferCallback),
    });
}

void JMediaPlayerData::sampleBufferCallback(jint sampleBuffer) {
    if (sampleBufferCallback_ == nullptr) {
        __android_log_write(ANDROID_LOG_WARN, TAG, "Sample Buffer Callback is null!");
        setEnableSampleBufferCallback(false);
        return;
    }

    auto sampleBufferStrong = /* TODO: make_local(sampleBuffer); */ sampleBuffer;
    try {
        sampleBufferCallback_(sampleBufferStrong);
    } catch (const std::exception& exception) {
        auto message = "Sample Buffer Callback threw an error! " + std::string(exception.what());
        __android_log_write(ANDROID_LOG_ERROR, TAG, message.c_str());
    }
}

void JMediaPlayerData::setEnableSampleBufferCallback(bool enable) {
    if (enable) {
        __android_log_write(ANDROID_LOG_INFO, TAG, "Enabling Sample Buffer Callback...");
    } else {
        __android_log_write(ANDROID_LOG_INFO, TAG, "Disabling Sample Buffer Callback...");
    }
    static const auto javaMethod = javaPart_->getClass()->getMethod<void(bool)>("setEnableSampleBufferCallback");
    javaMethod(javaPart_.get(), enable);
}

void JMediaPlayerData::setSampleBufferCallback(const SampleBufferCallback &&sampleBufferCallback) {
    sampleBufferCallback_ = sampleBufferCallback;
    setEnableSampleBufferCallback(true);
}

void JMediaPlayerData::unsetSampleBufferCallback() {
    sampleBufferCallback_ = nullptr;
    setEnableSampleBufferCallback(false);
}

} // namespace expo
