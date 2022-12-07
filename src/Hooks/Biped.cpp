#include "Biped.h"

#include "RE/Offset.h"

namespace Hooks
{
	void Biped::Install()
	{
#ifndef SKYRIMVR
		static const auto hook = util::MakeHook(RE::Offset::TESNPC::DismemberHeadParts, 0xD2);

		if (!REL::make_pattern<"44 0F B6 8D 40 02 00 00">().match(hook.address())) {
			util::report_and_fail("Biped::BeardSlotPatch failed to install"sv);
		}

		struct Patch : Xbyak::CodeGenerator
		{
			Patch()
			{
				mov(r8d, r12d);
				mov(rdx, rsi);
				mov(rcx, rbp);
				mov(rax, reinterpret_cast<std::uintptr_t>(&DismemberBeard));
				call(rax);

				movzx(r9d, byte[rbp + offsetof(RE::TESNPC, numHeadParts)]);

				jmp(ptr[rip]);
				dq(hook.address() + 0x8);
			}
		};

		Patch patch{};

		auto& trampoline = SKSE::GetTrampoline();
		trampoline.write_branch<6>(hook.address(), trampoline.allocate(patch));
#else
		static const auto hook = util::MakeHook(RE::Offset::TESNPC::DismemberHeadParts, 0xCD);

		if (!REL::make_pattern<"E8">().match(hook.address())) {
			util::report_and_fail("Biped::BeardSlotPatch failed to install"sv);
		}

		struct Patch : Xbyak::CodeGenerator
		{
			Patch()
			{
				mov(r8d, r12d);
				mov(rdx, rdi);
				mov(rax, reinterpret_cast<std::uintptr_t>(&DismemberBeard));
				call(rax);

				jmp(ptr[rip]);
				dq(hook.address() + 0x5);
			}
		};

		Patch patch{};

		auto& trampoline = SKSE::GetTrampoline();
		_FindHeadPart = trampoline.write_branch<5>(hook.address(), trampoline.allocate(patch));
#endif
	}

	IF_SKYRIMSE(void, RE::BGSHeadPart*) Biped::DismemberBeard(
		RE::TESNPC* a_npc,
		RE::NiAVObject* a_actor3D,
		std::uint32_t a_wornMask)
	{
#ifdef SKYRIMVR
		auto result = _FindHeadPart(a_npc, RE::BGSHeadPart::HeadPartType::kHair);
#endif

		static constexpr std::uint32_t beardSlot = 1U << (44 - 30);
		bool wearingBeardSlot = (a_wornMask & beardSlot) != 0;

		RE::BGSHeadPart* beard = nullptr;
		for (const auto& headPart : std::span(a_npc->headParts, a_npc->numHeadParts)) {
			if (headPart->type == RE::BGSHeadPart::HeadPartType::kFacialHair) {
				beard = headPart;
				break;
			}
		}

		if (!beard) {
			return IF_SKYRIMSE(, result);
		}

		if (auto beard3D = a_actor3D->GetObjectByName(beard->formEditorID)) {
			if (wearingBeardSlot) {
				beard3D->flags.set(RE::NiAVObject::Flag::kHidden);
			}
			else {
				beard3D->flags.reset(RE::NiAVObject::Flag::kHidden);
			}
		}

		for (const auto& extraPart : beard->extraParts) {
			if (auto extra3D = a_actor3D->GetObjectByName(extraPart->formEditorID)) {
				if (wearingBeardSlot) {
					extra3D->flags.set(RE::NiAVObject::Flag::kHidden);
				}
				else {
					extra3D->flags.reset(RE::NiAVObject::Flag::kHidden);
				}
			}
		}

		return IF_SKYRIMSE(, result);
	}
}
