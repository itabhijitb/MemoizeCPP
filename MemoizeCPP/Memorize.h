
#include <functional>
#include <tuple>
#include <map>
#ifndef __MEMORIZATION__H__
#define __MEMORIZATION__H__
namespace Memorization
{
	struct Memorize
	{
		template<typename _TyRet,
			typename TyPObj,
			typename TyClass,
			typename _FtypesFirst,
			typename _FtypesSecond,
			typename... _FtypesRest
		> inline
		std::function<_TyRet(_FtypesFirst, _FtypesSecond, _FtypesRest ...)>
		Memoize(_TyRet(TyClass::*_Pfx)(_FtypesFirst, _FtypesSecond, _FtypesRest ...), const TyPObj pObj)
		{
			static std::map<std::tuple<_FtypesFirst, _FtypesSecond, _FtypesRest ...>, _TyRet> memo;
			auto helper = [=](_FtypesFirst&& _ArgsFirst, _FtypesSecond&& _ArgsSecond, _FtypesRest&& ..._ArgsRest) mutable
			{
				auto key = std::make_tuple(
					std::forward<_FtypesFirst>(_ArgsFirst),
					std::forward<_FtypesSecond>(_ArgsSecond),
					std::forward<_FtypesRest>(_ArgsRest)...);
				if (memo.count(key) == 0)
				{
					memo[key] = (*pObj.*_Pfx)(
						std::forward<_FtypesFirst>(_ArgsFirst),
						std::forward<_FtypesSecond>(_ArgsSecond),
						std::forward<_FtypesRest>(_ArgsRest)...);
				}
				return memo[key];
			};
			return helper;
		};

		template<typename _TyRet,
			typename TyPObj,
			typename TyClass,
			typename _Ftypes
		> inline
		std::function<_TyRet(_Ftypes)>
		Memoize(_TyRet(TyClass::*_Pfx)(_Ftypes), const TyPObj pObj)
		{
			static std::map<_Ftypes, _TyRet> memo;
			return [=](_Ftypes&& _Args) mutable
			{
				auto key = _Args;
				if (memo.count(key) == 0)
				{
					memo[key] = (*pObj.*_Pfx)(key);
				}
				return memo[key];
			};
		};
	};
}
#endif