#include "mvInputItems.h"
#include "mvTypeBases.h"
#include <utility>
#include "mvValueStorage.h"
#include "mvMarvel.h"
#include "mvApp.h"
#include <string>

namespace Marvel {

    //-----------------------------------------------------------------------------
    // mvInputInt
    //-----------------------------------------------------------------------------
    mvInputInt::mvInputInt(const std::string& name, int default_value, const std::string& dataSource)
        : mvIntPtrBase(name, default_value, dataSource)
    {
        m_description.disableAllowed = true;
    }
    
    void mvInputInt::setEnabled(bool value)
    {
        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiInputTextFlags_ReadOnly;
            m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        }

        m_enabled = value;
    }

    void mvInputInt::draw()
    {
        auto styleManager = m_styleManager.getScopedStyleManager();
        ScopedID id;
        mvImGuiThemeScope scope(this);

        if (!m_enabled)
        {
            ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
            disabled_color.w = 0.392f;
            styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
        }

        if (ImGui::InputInt(m_label.c_str(), m_value, m_step, m_step_fast, m_flags))
        {
            // determines clamped cases
            //if the value is aboved a clamped value we will do like drag and slider and not run the callback
            if (m_min_clamped && m_max_clamped)
            {
                if (m_value[0] < m_min) m_value[0] = m_min;
                else if (m_value[0] > m_max) m_value[0] = m_max;
                else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
            }
            else if (m_min_clamped)
            {
                if (m_value[0] < m_min) m_value[0] = m_min;
                else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
            }
            else if (m_max_clamped)
            {
                if (m_value[0] > m_max) m_value[0] = m_max;
                else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
            }
            else
                mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
        }

    }

    void mvInputInt::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        if (PyObject* item = PyDict_GetItemString(dict, "on_enter")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_EnterReturnsTrue : m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        if (PyObject* item = PyDict_GetItemString(dict, "readonly")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_ReadOnly : m_flags &= ~ImGuiInputTextFlags_ReadOnly;
        if (PyObject* item = PyDict_GetItemString(dict, "step")) m_step = ToInt(item);
        if (PyObject* item = PyDict_GetItemString(dict, "step_fast")) m_step_fast = ToInt(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) { m_min = ToInt(item); m_min_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) { m_max = ToInt(item); m_max_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "min_clamped")) m_min_clamped = ToBool(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_clamped")) m_max_clamped = ToBool(item);
    }

    void mvInputInt::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        PyDict_SetItemString(dict, "on_enter", ToPyBool(m_flags & ImGuiInputTextFlags_EnterReturnsTrue));
        PyDict_SetItemString(dict, "readonly", ToPyBool(m_flags & ImGuiInputTextFlags_ReadOnly));
        PyDict_SetItemString(dict, "step", ToPyInt(m_step));
        PyDict_SetItemString(dict, "step_fast", ToPyInt(m_step_fast));
        PyDict_SetItemString(dict, "min_value", ToPyInt(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyInt(m_max));
        PyDict_SetItemString(dict, "min_clamped", ToPyBool(m_min_clamped));
        PyDict_SetItemString(dict, "max_clamped", ToPyBool(m_max_clamped));

    }

    //-----------------------------------------------------------------------------
    // mvInputInt2
    //-----------------------------------------------------------------------------
    mvInputInt2::mvInputInt2(const std::string& name, int* default_value, const std::string& dataSource)
        : mvInt2PtrBase(name, default_value, dataSource)
    {
        m_description.disableAllowed = true;
    }

    void mvInputInt2::setEnabled(bool value)
    {
        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiInputTextFlags_ReadOnly;
            m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        }

        m_enabled = value;
    }

    void mvInputInt2::draw()
    {
        auto styleManager = m_styleManager.getScopedStyleManager();
        ScopedID id;
        mvImGuiThemeScope scope(this);

        if (!m_enabled)
        {
            ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
            disabled_color.w = 0.392f;
            styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
        }

        if (ImGui::InputInt2(m_label.c_str(), m_value, m_flags))
        {
            // determines clamped cases
            //if the value is aboved a clamped value we will do like drag and slider and not run the callback
            if (m_min_clamped && m_max_clamped)
            {
                for (int i = 0; i < 2; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_min_clamped)
            {
                for (int i = 0 ; i < 2 ; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_max_clamped)
            {
                for (int i = 0; i < 2; i++)
                {
                    if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else
                mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
        }
    }

    void mvInputInt2::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        if (PyObject* item = PyDict_GetItemString(dict, "on_enter")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_EnterReturnsTrue : m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        if (PyObject* item = PyDict_GetItemString(dict, "readonly")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_ReadOnly : m_flags &= ~ImGuiInputTextFlags_ReadOnly;
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) { m_min = ToInt(item); m_min_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) { m_max = ToInt(item); m_max_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "min_clamped")) m_min_clamped = ToBool(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_clamped")) m_max_clamped = ToBool(item);
    }

    void mvInputInt2::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        PyDict_SetItemString(dict, "on_enter", ToPyBool(m_flags & ImGuiInputTextFlags_EnterReturnsTrue));
        PyDict_SetItemString(dict, "readonly", ToPyBool(m_flags & ImGuiInputTextFlags_ReadOnly));
        PyDict_SetItemString(dict, "min_value", ToPyInt(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyInt(m_max));
        PyDict_SetItemString(dict, "min_clamped", ToPyBool(m_min_clamped));
        PyDict_SetItemString(dict, "max_clamped", ToPyBool(m_max_clamped));

    }

    //-----------------------------------------------------------------------------
    // mvInputInt3
    //-----------------------------------------------------------------------------
    mvInputInt3::mvInputInt3(const std::string& name, int* default_value, const std::string& dataSource)
        : mvInt3PtrBase(name, default_value, dataSource)
    {
        m_description.disableAllowed = true;
    }

    void mvInputInt3::setEnabled(bool value)
    {
        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiInputTextFlags_ReadOnly;
            m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        }

        m_enabled = value;
    }

    void mvInputInt3::draw()
    {
        auto styleManager = m_styleManager.getScopedStyleManager();
        ScopedID id;
        mvImGuiThemeScope scope(this);

        if (!m_enabled)
        {
            ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
            disabled_color.w = 0.392f;
            styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
        }

        if (ImGui::InputInt3(m_label.c_str(), m_value, m_flags))
        {
            // determines clamped cases
            //if the value is aboved a clamped value we will do like drag and slider and not run the callback
            if (m_min_clamped && m_max_clamped)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_min_clamped)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_max_clamped)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else
                mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
        }
    }

    void mvInputInt3::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        if (PyObject* item = PyDict_GetItemString(dict, "on_enter")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_EnterReturnsTrue : m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        if (PyObject* item = PyDict_GetItemString(dict, "readonly")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_ReadOnly : m_flags &= ~ImGuiInputTextFlags_ReadOnly;
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) { m_min = ToInt(item); m_min_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) { m_max = ToInt(item); m_max_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "min_clamped")) m_min_clamped = ToBool(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_clamped")) m_max_clamped = ToBool(item);
    }

    void mvInputInt3::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        PyDict_SetItemString(dict, "on_enter", ToPyBool(m_flags & ImGuiInputTextFlags_EnterReturnsTrue));
        PyDict_SetItemString(dict, "readonly", ToPyBool(m_flags & ImGuiInputTextFlags_ReadOnly));
        PyDict_SetItemString(dict, "min_value", ToPyInt(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyInt(m_max));
        PyDict_SetItemString(dict, "min_clamped", ToPyBool(m_min_clamped));
        PyDict_SetItemString(dict, "max_clamped", ToPyBool(m_max_clamped));
    }

    //-----------------------------------------------------------------------------
    // mvInputInt4
    //-----------------------------------------------------------------------------
    mvInputInt4::mvInputInt4(const std::string& name, int* default_value, const std::string& dataSource)
        : mvInt4PtrBase(name, default_value, dataSource)
    {
        m_description.disableAllowed = true;
    }

    void mvInputInt4::setEnabled(bool value)
    {
        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiInputTextFlags_ReadOnly;
            m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        }

        m_enabled = value;
    }

    void mvInputInt4::draw()
    {
        auto styleManager = m_styleManager.getScopedStyleManager();
        ScopedID id;
        mvImGuiThemeScope scope(this);

        if (!m_enabled)
        {
            ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
            disabled_color.w = 0.392f;
            styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
        }

        if (ImGui::InputInt4(m_label.c_str(), m_value, m_flags))
        {
            // determines clamped cases
            //if the value is aboved a clamped value we will do like drag and slider and not run the callback
            if (m_min_clamped && m_max_clamped)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_min_clamped)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_max_clamped)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else
                mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
        }
    }

    void mvInputInt4::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        if (PyObject* item = PyDict_GetItemString(dict, "on_enter")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_EnterReturnsTrue : m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        if (PyObject* item = PyDict_GetItemString(dict, "readonly")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_ReadOnly : m_flags &= ~ImGuiInputTextFlags_ReadOnly;
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) { m_min = ToInt(item); m_min_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) { m_max = ToInt(item); m_max_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "min_clamped")) m_min_clamped = ToBool(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_clamped")) m_max_clamped = ToBool(item);
    }

    void mvInputInt4::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        PyDict_SetItemString(dict, "on_enter", ToPyBool(m_flags & ImGuiInputTextFlags_EnterReturnsTrue));
        PyDict_SetItemString(dict, "readonly", ToPyBool(m_flags & ImGuiInputTextFlags_ReadOnly));
        PyDict_SetItemString(dict, "min_value", ToPyInt(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyInt(m_max));
        PyDict_SetItemString(dict, "min_clamped", ToPyBool(m_min_clamped));
        PyDict_SetItemString(dict, "max_clamped", ToPyBool(m_max_clamped));
    }

    //-----------------------------------------------------------------------------
    // mvInputFloat
    //-----------------------------------------------------------------------------
    mvInputFloat::mvInputFloat(const std::string& name, float default_value, const std::string& dataSource)
        : mvFloatPtrBase(name, default_value, dataSource)
    {
        m_description.disableAllowed = true;
    }

    void mvInputFloat::setEnabled(bool value)
    {
        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiInputTextFlags_ReadOnly;
            m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        }

        m_enabled = value;
    }

    void mvInputFloat::draw()
    {
        auto styleManager = m_styleManager.getScopedStyleManager();
        ScopedID id;
        mvImGuiThemeScope scope(this);

        if (!m_enabled)
        {
            ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
            disabled_color.w = 0.392f;
            styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
        }

        if (ImGui::InputFloat(m_label.c_str(), m_value, m_step, m_step_fast, m_format.c_str(), m_flags))
        {
            // determines clamped cases
            //if the value is aboved a clamped value we will do like drag and slider and not run the callback
            if (m_min_clamped && m_max_clamped)
            {
                if (m_value[0] < m_min) m_value[0] = m_min;
                else if (m_value[0] > m_max) m_value[0] = m_max;
                else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
            }
            else if (m_min_clamped)
            {
                if (m_value[0] < m_min) m_value[0] = m_min;
                else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
            }
            else if (m_max_clamped)
            {
                if (m_value[0] > m_max) m_value[0] = m_max;
                else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
            }
            else
                mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
        }
    }

    void mvInputFloat::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;
         
        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "step")) m_step = ToFloat(item);
        if (PyObject* item = PyDict_GetItemString(dict, "step_fast")) m_step_fast = ToFloat(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) { m_min = ToFloat(item); m_min_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) { m_max = ToFloat(item); m_max_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "min_clamped")) m_min_clamped = ToBool(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_clamped")) m_max_clamped = ToBool(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
        flagop("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

    }

    void mvInputFloat::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;
         
        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "step", ToPyFloat(m_step));
        PyDict_SetItemString(dict, "step_fast", ToPyFloat(m_step_fast));
        PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));
        PyDict_SetItemString(dict, "min_clamped", ToPyBool(m_min_clamped));
        PyDict_SetItemString(dict, "max_clamped", ToPyBool(m_max_clamped));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
        checkbitset("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

    }

    //-----------------------------------------------------------------------------
    // mvInputFloat2
    //-----------------------------------------------------------------------------
    mvInputFloat2::mvInputFloat2(const std::string& name, float* default_value, const std::string& dataSource)
        : mvFloat2PtrBase(name, default_value, dataSource)
    {
        m_description.disableAllowed = true;
    }

    void mvInputFloat2::setEnabled(bool value)
    {
        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiInputTextFlags_ReadOnly;
            m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        }

        m_enabled = value;
    }

    void mvInputFloat2::draw()
    {
        auto styleManager = m_styleManager.getScopedStyleManager();
        ScopedID id;
        mvImGuiThemeScope scope(this);

        if (!m_enabled)
        {
            ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
            disabled_color.w = 0.392f;
            styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
        }

        if (ImGui::InputFloat2(m_label.c_str(), m_value, m_format.c_str(), m_flags))
        {
            // determines clamped cases
            //if the value is aboved a clamped value we will do like drag and slider and not run the callback
            if (m_min_clamped && m_max_clamped)
            {
                for (int i = 0; i < 2; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_min_clamped)
            {
                for (int i = 0; i < 2; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_max_clamped)
            {
                for (int i = 0; i < 2; i++)
                {
                    if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else
                mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
        }
    }

    void mvInputFloat2::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;
         
        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) { m_min = ToFloat(item); m_min_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) { m_max = ToFloat(item); m_max_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "min_clamped")) m_min_clamped = ToBool(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_clamped")) m_max_clamped = ToBool(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
        flagop("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

    }

    void mvInputFloat2::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;
         
        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));
        PyDict_SetItemString(dict, "min_clamped", ToPyBool(m_min_clamped));
        PyDict_SetItemString(dict, "max_clamped", ToPyBool(m_max_clamped));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
        checkbitset("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

    }

    //-----------------------------------------------------------------------------
    // mvInputFloat3
    //-----------------------------------------------------------------------------
    mvInputFloat3::mvInputFloat3(const std::string& name, float* default_value, const std::string& dataSource)
        : mvFloat3PtrBase(name, default_value, dataSource)
    {
        m_description.disableAllowed = true;
    }

    void mvInputFloat3::setEnabled(bool value)
    {
        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiInputTextFlags_ReadOnly;
            m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        }

        m_enabled = value;
    }

    void mvInputFloat3::draw()
    {
        auto styleManager = m_styleManager.getScopedStyleManager();
        ScopedID id;
        mvImGuiThemeScope scope(this);

        if (!m_enabled)
        {
            ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
            disabled_color.w = 0.392f;
            styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
        }

        if (ImGui::InputFloat3(m_label.c_str(), m_value, m_format.c_str(), m_flags))
        {
            // determines clamped cases
            //if the value is aboved a clamped value we will do like drag and slider and not run the callback
            if (m_min_clamped && m_max_clamped)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_min_clamped)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_max_clamped)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else
                mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
        }
    }

    void mvInputFloat3::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;
         
        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) { m_min = ToFloat(item); m_min_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) { m_max = ToFloat(item); m_max_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "min_clamped")) m_min_clamped = ToBool(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_clamped")) m_max_clamped = ToBool(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
        flagop("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

    }

    void mvInputFloat3::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;
         
        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));
        PyDict_SetItemString(dict, "min_clamped", ToPyBool(m_min_clamped));
        PyDict_SetItemString(dict, "max_clamped", ToPyBool(m_max_clamped));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
        checkbitset("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

    }

    //-----------------------------------------------------------------------------
    // mvInputFloat4
    //-----------------------------------------------------------------------------
    mvInputFloat4::mvInputFloat4(const std::string& name, float* default_value, const std::string& dataSource)
        : mvFloat4PtrBase(name, default_value, dataSource)
    {
        m_description.disableAllowed = true;
    }

    void mvInputFloat4::setEnabled(bool value)
    {
        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiInputTextFlags_ReadOnly;
            m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
        }

        m_enabled = value;
    }

    void mvInputFloat4::draw()
    {
        auto styleManager = m_styleManager.getScopedStyleManager();
        ScopedID id;
        mvImGuiThemeScope scope(this);

        if (!m_enabled)
        {
            ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
            disabled_color.w = 0.392f;
            styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
            styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
            styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
        }

        if (ImGui::InputFloat4(m_label.c_str(), m_value, m_format.c_str(), m_flags))
        {
            // determines clamped cases
            //if the value is aboved a clamped value we will do like drag and slider and not run the callback
            if (m_min_clamped && m_max_clamped)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_min_clamped)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (m_value[i] < m_min) m_value[i] = m_min;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else if (m_max_clamped)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (m_value[i] > m_max) m_value[i] = m_max;
                    else mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
                }
            }
            else
                mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);
        }
    }

    void mvInputFloat4::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;
         
        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) { m_min = ToFloat(item); m_min_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) { m_max = ToFloat(item); m_max_clamped = true; }
        if (PyObject* item = PyDict_GetItemString(dict, "min_clamped")) m_min_clamped = ToBool(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_clamped")) m_max_clamped = ToBool(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
        flagop("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

    }

    void mvInputFloat4::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;
         
        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));
        PyDict_SetItemString(dict, "min_clamped", ToPyBool(m_min_clamped));
        PyDict_SetItemString(dict, "max_clamped", ToPyBool(m_max_clamped));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
        checkbitset("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);
    }

}
