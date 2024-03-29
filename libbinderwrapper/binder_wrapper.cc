/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <binderwrapper/binder_wrapper.h>

#include <android-base/logging.h>

#include "real_binder_wrapper.h"

namespace android {

// Singleton instance.
BinderWrapper* BinderWrapper::instance_ = nullptr;

// static
void BinderWrapper::Create() {
  CHECK(!instance_) << "Already initialized; missing call to Destroy()?";
  instance_ = new RealBinderWrapper();
}

// static
void BinderWrapper::InitForTesting(BinderWrapper* wrapper) {
  CHECK(!instance_) << "Already initialized; missing call to Destroy()?";
  instance_ = wrapper;
}

// static
void BinderWrapper::Destroy() {
  CHECK(instance_) << "Not initialized; missing call to Create()?";
  delete instance_;
  instance_ = nullptr;
}

// static
BinderWrapper* BinderWrapper::Get() {
  CHECK(instance_) << "Not initialized; missing call to Create()?";
  return instance_;
}

// static
BinderWrapper* BinderWrapper::GetOrCreateInstance() {
  if (!instance_)
    instance_ = new RealBinderWrapper();
  return instance_;
}

}  // namespace android
