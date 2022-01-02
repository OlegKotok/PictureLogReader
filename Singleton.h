/*! FILENAME:  Singleton.h
 *  DESCRIPTION:  Helper. Implementation of singleton pattern
 */

#ifndef SINGLETON_H
#define SINGLETON_H

#include <QDebug>


template <typename T>
class Singleton
{
public:

    /** Function Description: Getter for singleton instance */
    static T* getInstance()
    {
        if (!m_st_instance_p)
        {
            m_st_instance_p = new T;
            qDebug()<<"Created new singeltone instance";
        }
        return m_st_instance_p;
    }

    /** Function Description: Deleter for singleton instance */
    static void deleteInstance()
    {
        delete m_st_instance_p;
    }

    /** Function Description: prohibition of copy constructor */
    Singleton (const Singleton&) = delete;

    /** Function Description: prohibition of copy by equal operator */
    Singleton& operator= (const Singleton &) = delete;

    /** Function Description: prohibition of copy by lref operator */
    Singleton (Singleton &&) = delete;

    /** Function Description: prohibition of copy by lref equal operator */
    Singleton & operator=(Singleton &&) = delete;

protected:
    /** Function Description: singleton constructor */
    Singleton() {}

    ///< Function Description: singleton destructor */
    ~Singleton() {}

private:
    static T* m_st_instance_p;
};

#endif // SINGLETON_H
