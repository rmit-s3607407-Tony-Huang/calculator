// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "../Common/Utils.h"

namespace CalculatorApp::ViewModel
{
#pragma once
    [Windows::UI::Xaml::Data::Bindable] public ref class GraphingSettingsViewModel sealed : public Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    public:
        OBSERVABLE_OBJECT();
        OBSERVABLE_PROPERTY_R(bool, YMinError);
        OBSERVABLE_PROPERTY_R(bool, XMinError);
        OBSERVABLE_PROPERTY_R(bool, XMaxError);
        OBSERVABLE_PROPERTY_R(bool, YMaxError);
        OBSERVABLE_PROPERTY_R(GraphControl::Grapher ^, Graph);

        GraphingSettingsViewModel();

        property bool XError
        {
            bool get()
            {
                return !m_XMinError && !m_XMaxError && m_XMinValue >= m_XMaxValue;
            }
        }

        property bool YError
        {
            bool get()
            {
                return !m_YMinError && !m_YMaxError && m_YMinValue >= m_YMaxValue;
            }
        }

        property Platform::String ^ XMin
        {
            Platform::String ^ get()
            {
                return m_XMin;
            }
            void set(Platform::String ^ value)
            {
                if (m_XMin == value)
                {
                    return;
                }
                m_XMin = value;
                m_XIsMinLastChanged = true;
                if (m_Graph != nullptr)
                {
                    try
                    {
                        size_t sz;
                        auto number = std::stod(value->Data(), &sz);
                        if (value->Length() == sz)
                        {
                            m_Graph->XAxisMin = m_XMinValue = number;
                            XMinError = false;
                        }
                        else
                        {
                            XMinError = true;
                        }
                    }
                    catch (...)
                    {
                        XMinError = true;
                    }
                }
                RaisePropertyChanged("XError");
                RaisePropertyChanged("XMin");
                UpdateDisplayRange(true);
            }
        }

        property Platform::String ^ XMax
        {
            Platform::String ^ get()
            {
                return m_XMax;
            }
            void set(Platform::String ^ value)
            {
                if (m_XMax == value)
                {
                    return;
                }
                m_XMax = value;
                m_XIsMinLastChanged = false;
                if (m_Graph != nullptr)
                {
                    try
                    {
                        size_t sz;
                        auto number = std::stod(value->Data(), &sz);
                        if (value->Length() == sz)
                        {
                            m_Graph->XAxisMax = m_XMaxValue = number;
                            XMaxError = false;
                        }
                        else
                        {
                            XMaxError = true;
                        }
                    }
                    catch (...)
                    {
                        XMaxError = true;
                    }
                }
                RaisePropertyChanged("XError");
                RaisePropertyChanged("XMax");
                UpdateDisplayRange(true);
            }
        }

        property Platform::String ^ YMin
        {
            Platform::String ^ get()
            {
                return m_YMin;
            }
            void set(Platform::String ^ value)
            {
                if (m_YMin == value)
                {
                    return;
                }
                m_YMin = value;
                m_YIsMinLastChanged = true;
                if (m_Graph != nullptr)
                {
                    try
                    {
                        size_t sz;
                        auto number = std::stod(value->Data(), &sz);
                        if (value->Length() == sz)
                        {
                            m_Graph->YAxisMin = m_YMinValue = number;
                            YMinError = false;
                        }
                        else
                        {
                            YMinError = true;
                        }
                    }
                    catch (...)
                    {
                        YMinError = true;
                    }
                }
                RaisePropertyChanged("YError");
                RaisePropertyChanged("YMin");
                UpdateDisplayRange(false);
            }
        }

        property Platform::String ^ YMax
        {
            Platform::String ^ get()
            {
                return m_YMax;
            }
            void set(Platform::String ^  value)
            {
                if (m_YMax == value)
                {
                    return;
                }
                m_YMax = value;
                m_YIsMinLastChanged = false;
                if (m_Graph != nullptr)
                {
                    try
                    {
                        size_t sz;
                        auto number = std::stod(value->Data(), &sz);
                        if (value->Length() == sz)
                        {
                            m_Graph->YAxisMax = m_YMaxValue = number;
                            YMaxError = false;
                        }
                        else
                        {
                            YMaxError = true;
                        }
                    }
                    catch (...)
                    {
                        YMaxError = true;
                    }
                }
                RaisePropertyChanged("YError");
                RaisePropertyChanged("YMax");
                UpdateDisplayRange(false);
            }
        }

        property int TrigUnit
        {
            int get()
            {
                return m_Graph == nullptr ? (int)Graphing::EvalTrigUnitMode::Invalid : m_Graph->TrigUnitMode;
            }
            void set(int value)
            {
                if (m_Graph == nullptr)
                {
                    return;
                }
                m_Graph->TrigUnitMode = value;
                RaisePropertyChanged(L"TrigUnit");
            }
        }

        property bool TrigModeRadians
        {
            bool get()
            {
                return m_Graph != nullptr && m_Graph->TrigUnitMode == (int)Graphing::EvalTrigUnitMode::Radians;
            }
            void set(bool value)
            {
                if (value && m_Graph != nullptr && m_Graph->TrigUnitMode != (int)Graphing::EvalTrigUnitMode::Radians)
                {
                    m_Graph->TrigUnitMode = (int)Graphing::EvalTrigUnitMode::Radians;
                    RaisePropertyChanged(L"TrigModeRadians");
                    RaisePropertyChanged(L"TrigModeDegrees");
                    RaisePropertyChanged(L"TrigModeGradians");
                }
            }
        }

        property bool TrigModeDegrees
        {
            bool get()
            {
                return m_Graph != nullptr && m_Graph->TrigUnitMode == (int)Graphing::EvalTrigUnitMode::Degrees;
            }
            void set(bool value)
            {
                if (value && m_Graph != nullptr && m_Graph->TrigUnitMode != (int)Graphing::EvalTrigUnitMode::Degrees)
                {
                    m_Graph->TrigUnitMode = (int)Graphing::EvalTrigUnitMode::Degrees;
                    RaisePropertyChanged(L"TrigModeDegrees");
                    RaisePropertyChanged(L"TrigModeRadians");
                    RaisePropertyChanged(L"TrigModeGradians");
                }
            }
        }

        property bool TrigModeGradians
        {
            bool get()
            {
                return m_Graph != nullptr && m_Graph->TrigUnitMode == (int)Graphing::EvalTrigUnitMode::Grads;
            }
            void set(bool value)
            {
                if (value && m_Graph != nullptr && m_Graph->TrigUnitMode != (int)Graphing::EvalTrigUnitMode::Grads)
                {
                    m_Graph->TrigUnitMode = (int)Graphing::EvalTrigUnitMode::Grads;
                    RaisePropertyChanged(L"TrigModeGradians");
                    RaisePropertyChanged(L"TrigModeDegrees");
                    RaisePropertyChanged(L"TrigModeRadians");
                }
            }
        }

    public:
        void UpdateDisplayRange(bool XValuesModified);

    public:
        void SetGrapher(GraphControl::Grapher ^ grapher);
        void InitRanges();
        bool HasError();

    private:
        Platform::String ^ m_XMin;
        Platform::String ^ m_XMax;
        Platform::String ^ m_YMin;
        Platform::String ^ m_YMax;
        double m_XMinValue;
        double m_XMaxValue;
        double m_YMinValue;
        double m_YMaxValue;
        bool m_dontUpdateDisplayRange;
        bool m_XIsMinLastChanged;
        bool m_YIsMinLastChanged;
    };
}
