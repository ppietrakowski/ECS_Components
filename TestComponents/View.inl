
template <typename T>
inline View<T>::View(const std::vector<int>* entities, ComponentHolder* holder) :
    Entities(entities),
    Holder(holder)
{
    assert(Entities != nullptr);
    assert(Holder != nullptr);
}

template <typename T>
inline void View<T>::ForEach(std::function<void(int id, T& component)> fn)
{
    for (int i : *Entities)
    {
        if (Holder->HasComponent<T>(i))
        {
            fn(i, Holder->GetComponent<T>(i));
        }
    }
}

template <typename T>
inline auto View<T>::begin()
{
    return Holder->begin<T>();
}

template <typename T>
inline auto View<T>::end()
{
    return Holder->end<T>();
}