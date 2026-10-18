#pragma once

#include "esphome/core/automation.h"
#include "switchbot_keypad_bridge.h"

namespace esphome {
namespace switchbot_keypad_bridge {

template<typename... Ts> class RearmAction : public Action<Ts...> {
 public:
  explicit RearmAction(SwitchbotKeypadBridge *parent) : parent_(parent) {}
  void play(const Ts &...x) override { this->parent_->rearm(); }

 protected:
  SwitchbotKeypadBridge *parent_;
};

template<typename... Ts> class UnlockAction : public Action<Ts...> {
 public:
  explicit UnlockAction(SwitchbotKeypadBridge *parent) : parent_(parent) {}
  void play(const Ts &...x) override { this->parent_->unlock_lock(); }

 protected:
  SwitchbotKeypadBridge *parent_;
};

template<typename... Ts> class LockAction : public Action<Ts...> {
 public:
  explicit LockAction(SwitchbotKeypadBridge *parent) : parent_(parent) {}
  void play(const Ts &...x) override { this->parent_->lock_lock(); }

 protected:
  SwitchbotKeypadBridge *parent_;
};

class LockTrigger : public Trigger<> {
 public:
  explicit LockTrigger(SwitchbotKeypadBridge *parent) {
    parent->add_on_lock_callback([this]() { this->trigger(); });
  }
};

class UnlockTrigger : public Trigger<std::string, int> {
 public:
  explicit UnlockTrigger(SwitchbotKeypadBridge *parent) {
    parent->add_on_unlock_callback(
        [this](const std::string &method, int index) { this->trigger(method, index); });
  }
};

class DoorbellTrigger : public Trigger<> {
 public:
  explicit DoorbellTrigger(SwitchbotKeypadBridge *parent) {
    parent->add_on_doorbell_callback([this]() { this->trigger(); });
  }
};

}  // namespace switchbot_keypad_bridge
}  // namespace esphome
