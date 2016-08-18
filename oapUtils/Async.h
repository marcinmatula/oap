
#ifndef ASYNC_H
#define	ASYNC_H

#include "Callbacks.h"
#include "ThreadUtils.h"
#include <queue>

namespace utils {
    typedef void (*Action_f)(void* userPtr);

    class AsyncQueue : public CallbacksManager {
    public:
        static int EVENT_ACTION_DONE;

        AsyncQueue(Callbacks* callbacks = NULL);
        virtual ~AsyncQueue();

        LHandle execute(Action_f action, void* userPtr);

    private:
        void stop();

        class Action {
        public:
            Action_f action;
            void* userPtr;
        };

        pthread_t thread;
        utils::sync::Mutex mutex;
        utils::sync::Cond cond;
        bool stoped;
        std::queue<Action*> actions;

        static void* ExecuteMainThread(void* ptr);
        Callbacks callbacks;
    };

    class AsyncProcess : public CallbacksManager {
    public:
        AsyncProcess(AsyncQueue* async = NULL);
        virtual ~AsyncProcess();
    protected:
        AsyncQueue& getInstance() const;
    private:
        bool sharedAsync;
        AsyncQueue* async;
    };

}

#endif	/* ASYNCRANDOMS_H */

