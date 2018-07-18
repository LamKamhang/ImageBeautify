#pragma once

#include <memory>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include "parameters.h"
#include "type.h"

/*
 * class: ICommandBase
 * Version: 1.0
 * Author: kk
 * Created Date: Tue Jul 17 21:02:30 DST 2018
 * -------------------------------------------
 * 工厂类: ICommandBase
 * 		所有的Command都需要继承该基类，并实现exec
 * 		参数会在调用Command的同时进行set到params中
 */
class ICommandBase
{
public:
	// std::static_pointer_cast<deriveClass, ParametersBase>(param)->getvalue();
	virtual void SetParameter(const std::shared_ptr<ParametersBase>& param) = 0;

    virtual void Exec() = 0;
};

/*
 * class: Notification
 * Version: 1.0
 * Author: kk
 * Created Date: Tue Jul 17 21:02:30 DST 2018
 * -------------------------------------------
 * 工厂类: Notification
 * 		这里使用模板是由于属性以及命令两种通知需要区分开
 */
template <class T>
class INotification
{
public:
	void Clear() throw()
	{
		m_array.clear();
	}
	void AddNotification(const std::shared_ptr<T>& p)
	{
		m_array.push_back(p);
	}

protected:
    std::vector<std::shared_ptr<T> > m_array;
};

/*
 * class: PropertyNotification
 * Version: 1.0
 * Author: kk
 * Created Date: Tue Jul 17 21:02:30 DST 2018
 * -------------------------------------------
 * 工厂类: PropertyNotification
 * 		属性通知的工厂类, 属性改变后发通知
 */
class IPropertyNotification
{
public:
	virtual void OnPropertyChanged(const propertyType ppt) = 0;
};

/*
 * class: CommandNotification
 * Version: 1.0
 * Author: kk
 * Created Date: Tue Jul 17 21:02:30 DST 2018
 * -------------------------------------------
 * 工厂类: CommandNotification
 * 		命令通知的工厂类, 命令完成后发通知
 */
class ICommandNotification
{
public:
	virtual void OnCommandComplete(const commandsType cmd, bool OK) = 0;
};

/*
 * class: Proxy_PropertyNotification
 * Version: 1.0
 * Author: kk
 * Created Date: Tue Jul 17 21:02:30 DST 2018
 * -------------------------------------------
 * 工厂类: Proxy_PropertyNotification
 * 		属性通知代理
 */
template <class T>
class Proxy_PropertyNotification : public INotification<IPropertyNotification>
{
public:
    void AddPropertyNotification(const std::shared_ptr<IPropertyNotification>& p)
	{
		AddNotification(p);
	}
	void Fire_OnPropertyChanged(const propertyType ppt)
	{
		auto iter(m_array.begin());
		for( ; iter != m_array.end(); ++ iter ) {
			(*iter)->OnPropertyChanged(ppt);
		}
	}
};

/*
 * class: Proxy_CommandNotification
 * Version: 1.0
 * Author: kk
 * Created Date: Tue Jul 17 21:02:30 DST 2018
 * -------------------------------------------
 * 工厂类: Proxy_CommandNotification
 * 		命令通知代理
 */
template <class T>
class Proxy_CommandNotification : public INotification<ICommandNotification>
{
public:
    void AddCommandNotification(const std::shared_ptr<ICommandNotification>& p)
	{
		AddNotification(p);
	}
	void Fire_OnCommandComplete(const commandsType cmd, bool OK)
	{
		auto iter(m_array.begin());
		for( ; iter != m_array.end(); ++ iter ) {
			(*iter)->OnCommandComplete(cmd, OK);
		}
	}
};
