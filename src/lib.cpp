#include <emscripten/bind.h>
#include <emscripten/promise.h>
#include <thread>

emscripten::val do_thread_thing() {
  auto promise = emscripten_promise_create();

  std::thread([promise] {
    emscripten_promise_resolve(promise, EM_PROMISE_FULFILL, nullptr);
    emscripten_promise_destroy(promise);
  });

  return emscripten::val(promise);
}

EMSCRIPTEN_BINDINGS(module) {
  emscripten::function("do_thread_thing", &do_thread_thing, emscripten::allow_raw_pointers());
}
