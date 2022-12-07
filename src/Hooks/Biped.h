#include <xbyak/xbyak.h>

namespace Hooks
{
	class Biped
	{
	public:
		static void Install();

	private:

		static IF_SKYRIMSE(void, RE::BGSHeadPart*) DismemberBeard(
			RE::TESNPC* a_npc,
			RE::NiAVObject* a_actor3D,
			std::uint32_t a_wornMask);

	#ifdef SKYRIMVR
		inline static REL::Relocation<RE::BGSHeadPart* (*)(RE::TESNPC*, RE::BGSHeadPart::HeadPartType)>
			_FindHeadPart;
	#endif
	};
}
