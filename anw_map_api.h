#ifndef _ANW_MAP_API_H_
#define _ANW_MAP_API_H_
#include <map>

template<typename T1, typename T2>
ANW_RSP_STATUS anw_map_insert(T1 key, T2 obj, std::map<T1, T2> &m)
{

  std::pair<typename std::map<T1, T2>::iterator, bool> ret;

  ret = m.insert(std::make_pair(key, obj));
  if (false == ret.second)
  {
    return ANW_STATUS_FAILURE;
  }
  return ANW_STATUS_SUCCESS;
}

template<typename T1, typename T2>
ANW_RSP_STATUS anw_map_remove(T1 key, T2 *obj, std::map<T1, T2> &m)
{

  typename std::map<T1, T2>::iterator it;

  it = m.find(key);

  if (it != m.end())
  {
    *obj = it->second;
    m.erase(it);

    return ANW_STATUS_SUCCESS;
  }
  return ANW_STATUS_FAILURE;
}

template<typename T1, typename T2>
ANW_RSP_STATUS anw_map_find(T1 key, T2 *obj, std::map<T1, T2> &m)
{

  typename std::map<T1, T2>::iterator it;

  it = m.find(key);

  if (it != m.end())
  {
    *obj = it->second;
    return ANW_STATUS_SUCCESS;
  }

  return ANW_STATUS_FAILURE;
}
#endif //_ANW_MAP_API_H_
