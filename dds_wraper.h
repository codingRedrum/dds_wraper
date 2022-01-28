{% extends "license.j2" %}
{% block content %}

#include <dds/can/{{module_name}}.h>

namespace togg {
namespace dds {
namespace can {

class {{cpp_module_name}}
{
public:
    explicit {{cpp_module_name}}(const {{module_name}}_topic_data_t& contents)
        :m_contents(contents)
    {}

    template<typename F>
    decltype(auto) accept(F&& visitor)
  {
        switch(m_contents.u._d)
        {
        {% for msg in messages %}
            case {{module_name}}_{{msg.name.upper()}}:
                return visitor(m_contents.u._u.{{msg.name}});
            break;
        {% endfor %}
            default:
                throw std::runtime_error("Unknown message {{cpp_module_name}} contents id: " + std::to_string(static_cast<int>(m_contents.u._d)));
        }
    }
private:
    {{module_name}}_topic_data_t m_contents;
};

} // namespace can
} // namespace dds
} // namespace togg

{%endblock%}

