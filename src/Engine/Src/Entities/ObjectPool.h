#ifndef INC_2D_ENGINE_OBJECTPOOL_H
#define INC_2D_ENGINE_OBJECTPOOL_H

#include <vector>

namespace e2d
{
    template <class T>
    class ObjectPool
    {
    public:
        ObjectPool()
        {
            const int baseSize = 10;
            m_instancesFree.reserve(baseSize);
            initialFill(baseSize);
        }
        ObjectPool(int poolSize)
        {
            m_instancesFree.reserve(poolSize);
            initialFill(poolSize);
        }
        ~ObjectPool()
        {
            for(T* ptr : m_instancesFree)
            {
                delete ptr;
            }
            for(T* ptr : m_instancesUsed)
            {
                delete ptr;
            }
        }

        T* get() const
        {
            if(m_instancesFree.empty())
            {
                T* instance = new T;
                m_instancesUsed.push_back(instance);
                return instance;
            }

            T* instance = m_instancesFree.end();
            m_instancesFree.pop_back();
            m_instancesUsed.push_back(instance);
            return instance;
        }

        void release(T* instance)
        {
            for(typename std::vector<T*>::iterator it = m_instancesUsed.begin(); it != m_instancesUsed.end() ; )
            {
                if (m_instancesUsed.at(it) == instance)
                {
                    it = it.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            m_instancesFree.push_back(instance);
        }

    private:
        std::vector<T*> m_instancesFree;
        std::vector<T*> m_instancesUsed;

        void initialFill(int size)
        {
            for(int i = 0; i < size; i++)
            {
                m_instancesFree.push_back(new T);
            }
        }
    };
}


#endif //INC_2D_ENGINE_OBJECTPOOL_H
