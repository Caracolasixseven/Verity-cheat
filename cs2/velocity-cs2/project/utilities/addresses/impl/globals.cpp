#include <pch/pch.hpp>
#include <utilities/memory/memory.hpp>
#include <utilities/logging/logging.hpp>
#include <protection/game_addresses.hpp>
#include "../addresses.hpp"

namespace addresses::globals {

	bool initialize () {
		source2client              = INTERFACE_ ("Source2Client002");
		panorama = INTERFACE_ ("PanoramaUIEngine001");
		source2engine_to_client    = INTERFACE_ ("Source2EngineToClient001");
		scene_system               = INTERFACE_ ("SceneSystem_002");
		material_system            = INTERFACE_ ("VMaterialSystem2_001");
		schema_system              = INTERFACE_ ("SchemaSystem_001");
		input_system               = INTERFACE_ ("InputSystemVersion001");
		particle_system_mgr        = INTERFACE_ ("ParticleSystemMgr003");
		cvar                       = (interfaces::c_engine_cvar*)INTERFACE_ ("VEngineCvar007");
		source2client_prediction   = INTERFACE_ ("Source2ClientPrediction001");
		network_client_service     = INTERFACE_ ("NetworkClientService_001");
		resource_system            = INTERFACE_ ("ResourceSystem013");
		localize                   = INTERFACE_ ("Localize_001");
		mesh_system                = INTERFACE_ ("MeshSystem001");
		file_system                = INTERFACE_ ("VFileSystem017");

		// --- OFFSETS ESTÁTICOS (15/10/2026) ---
		// 1. Declaramos la base de client.dll para que no falle
		auto client = modules::client;

		csgo_input              = client + 0x257B640; // dwCSGOInput
		entity_list             = client + 0x271A908; // dwEntityList
		local_player_controller = client + 0x253CB78; // dwLocalPlayerController
		global_vars             = client + 0x2230090; // dwGlobalVars
		view_matrix             = client + 0x256B020; // dwViewMatrix
		game_rules              = client + 0x25651D0; // dwGameRules
		planted_c4              = client + 0x24CB3C0; // dwPlantedC4
		weapon_recoil_data      = client + 0x2562A18; // dwSensitivity
		
		// 2. Los patrones que se mantienen
		light_data_queue        = PATTERN (patterns::light_data_queue);
		particle_manager        = PATTERN (patterns::particle_manager);
		game_event_manager      = PATTERN (patterns::game_event_manager);
		game_trace_manager      = PATTERN (patterns::game_trace_manager);
		render_game_system      = PATTERN (patterns::render_game_system);
		material_manager        = PATTERN (patterns::material_manager);
		game_entity_system      = PATTERN (patterns::game_entity_system);
		hud                     = PATTERN (patterns::hud);
		prediction_seed         = PATTERN (patterns::prediction_seed);
		simulation_player       = PATTERN (patterns::simulation_player);
		prediction_player       = PATTERN (patterns::prediction_player);
		item_system             = PATTERN (patterns::item_system);
		net_client              = PATTERN (patterns::net_client);
		frame_input_ring_idx    = PATTERN (patterns::frame_input_ring_idx);
		frame_input_ring_base   = PATTERN (patterns::frame_input_ring_base);
		prediction_state        = PATTERN (patterns::prediction_state);
		
		if (const auto ptr = MODULE_EXPORT("tier0.dll:g_pMemAlloc"))
			mem_alloc = *reinterpret_cast<std::uintptr_t*>(ptr);

		{
			const auto storage = PATTERN (patterns::swap_chain_storage);
			if (!storage) {
				return false;
			}

			const auto first = memory::read<std::uintptr_t> (storage);
			if (!first) {
				return false;
			}

			const auto second = memory::read<std::uintptr_t> (first);
			if (!second) {
				return false;
			}

			swap_chain = memory::read<std::uintptr_t> (second + 0x170);
		}

		return true;
	}

} // namespace addresses::globals
