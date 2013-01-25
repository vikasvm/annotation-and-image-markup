//   Copyright (C) 2009, Vaclav Haisman. All rights reserved.
//
//   Redistribution and use in source and binary forms, with or without modifica-
//   tion, are permitted provided that the following conditions are met:
//
//   1. Redistributions of  source code must  retain the above copyright  notice,
//      this list of conditions and the following disclaimer.
//
//   2. Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the documentation
//      and/or other materials provided with the distribution.
//
//   THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED WARRANTIES,
//   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//   FITNESS  FOR A PARTICULAR  PURPOSE ARE  DISCLAIMED.  IN NO  EVENT SHALL  THE
//   APACHE SOFTWARE  FOUNDATION  OR ITS CONTRIBUTORS  BE LIABLE FOR  ANY DIRECT,
//   INDIRECT, INCIDENTAL, SPECIAL,  EXEMPLARY, OR CONSEQUENTIAL  DAMAGES (INCLU-
//   DING, BUT NOT LIMITED TO, PROCUREMENT  OF SUBSTITUTE GOODS OR SERVICES; LOSS
//   OF USE, DATA, OR  PROFITS; OR BUSINESS  INTERRUPTION)  HOWEVER CAUSED AND ON
//   ANY  THEORY OF LIABILITY,  WHETHER  IN CONTRACT,  STRICT LIABILITY,  OR TORT
//   (INCLUDING  NEGLIGENCE OR  OTHERWISE) ARISING IN  ANY WAY OUT OF THE  USE OF
//   THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef DCMTK_LOG4CPLUS_THREAD_SYNCPRIMS_H
#define DCMTK_LOG4CPLUS_THREAD_SYNCPRIMS_H

//#include <stdexcept>
#include "dcmtk/oflog/config.h"
#if defined (DCMTK_LOG4CPLUS_USE_PTHREADS)
#  define INCLUDE_CERRNO
#  include "dcmtk/ofstd/ofstdinc.h"

#  include <pthread.h>
#  include <semaphore.h>
#  include "dcmtk/oflog/helpers/timehelp.h"

#elif defined (DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
#  undef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>

#endif


namespace dcmtk { namespace log4cplus { namespace thread {


namespace detail
{

DCMTK_LOG4CPLUS_EXPORT void syncprims_throw_exception (char const * const msg,
    char const * const file, int line);

} // namespace detail


template <typename SP>
class SyncGuard
{
public:
    SyncGuard (SP const &);
    ~SyncGuard ();

    void lock ();
    void unlock ();
    void attach (SP const &);
    void detach ();

private:
    SP const * sp;

    SyncGuard (SyncGuard const &);
    SyncGuard & operator = (SyncGuard const &);
};


class ManualResetEvent;


class Mutex
{
public:
    Mutex ();
    ~Mutex ();

    void lock () const;
    void unlock () const;

private:
#if defined (DCMTK_LOG4CPLUS_USE_PTHREADS)
    mutable pthread_mutex_t mtx;
    friend class ManualResetEvent;
#elif defined (DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
    mutable CRITICAL_SECTION cs;
#endif

    Mutex (Mutex const &);
    Mutex & operator = (Mutex &);
};


typedef SyncGuard<Mutex> MutexGuard;


class Semaphore
{
public:
    Semaphore (unsigned max, unsigned initial);
    ~Semaphore ();

    void lock () const;
    void unlock () const;

private:
#if defined (DCMTK_LOG4CPLUS_USE_PTHREADS)
    mutable sem_t sem;
#elif defined (DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
    HANDLE sem;
#endif

    Semaphore (Semaphore const &);
    Semaphore & operator = (Semaphore const &);
};


typedef SyncGuard<Semaphore> SemaphoreGuard;


class ManualResetEvent
{
public:
    ManualResetEvent (bool = false);
    ~ManualResetEvent ();

    void signal () const;
    void wait () const;
    bool timed_wait (unsigned long msec) const;
    void reset () const;

private:
#if defined (DCMTK_LOG4CPLUS_USE_PTHREADS)
    mutable pthread_cond_t cv;
    mutable Mutex mtx;
    mutable volatile unsigned sigcount;
    mutable volatile bool signaled;
#elif defined (DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
    HANDLE ev;
#endif

    ManualResetEvent (ManualResetEvent const &);
    ManualResetEvent & operator = (ManualResetEvent const &);
};


} } } // namespace dcmtk { namespace log4cplus { namespace thread {


// Include the appropriate implementations of the classes declared
// above.

#if defined (DCMTK_LOG4CPLUS_USE_PTHREADS)
#  include "dcmtk/oflog/helpers/syncppth.h"
#elif defined (DCMTK_LOG4CPLUS_USE_WIN32_THREADS)
#  include "dcmtk/oflog/helpers/syncpwin.h"
#endif


namespace dcmtk { namespace log4cplus { namespace thread {


//
//
//

template <typename SP>
inline
SyncGuard<SP>::SyncGuard (SP const & m)
    : sp (&m)
{
    sp->lock ();
}


template <typename SP>
inline
SyncGuard<SP>::~SyncGuard ()
{
    if (sp)
        sp->unlock ();
}


template <typename SP>
inline
void
SyncGuard<SP>::lock ()
{
    sp->lock ();
}


template <typename SP>
inline
void
SyncGuard<SP>::unlock ()
{
    sp->unlock ();
}


template <typename SP>
inline
void
SyncGuard<SP>::attach (SP const & m)
{
    sp = &m;
}


template <typename SP>
inline
void
SyncGuard<SP>::detach ()
{
    sp = 0;
}


} } } // namespace dcmtk { namespace log4cplus { namespace thread {



#endif // DCMTK_LOG4CPLUS_THREAD_SYNCPRIMS_H
