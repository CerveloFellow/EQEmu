#include "zone/client.h"

void command_goto(Client* c, const Seperator* sep)
{
	const uint16 arguments = sep->argnum;

	// Check for "id" keyword as first argument
	const bool goto_spawn_id = arguments > 0 && strcasecmp(sep->arg[1], "id") == 0 && arguments > 1;
	const bool goto_player = arguments > 0 && !sep->IsNumber(1) && !goto_spawn_id;
	const bool goto_position = sep->IsNumber(1) && sep->IsNumber(2) && sep->IsNumber(3);
	const bool goto_target = !arguments && c->GetTarget();

	if (!goto_spawn_id && !goto_player && !goto_position && !goto_target) {
		c->Message(Chat::White, "Usage: #goto [x y z] [h]");
		c->Message(Chat::White, "Usage: #goto [player_name]");
		c->Message(Chat::White, "Usage: #goto id [spawn_id]");
		c->Message(Chat::White, "Usage: #goto (Target required)");
		return;
	}

	if (goto_spawn_id) {
		// Parse spawn ID from second argument
		uint32 spawn_id = 0;

		try {
			spawn_id = static_cast<uint32>(std::stoul(sep->arg[2]));
		}
		catch (...) {
			c->Message(Chat::White, "Invalid spawn ID. Usage: #goto id [spawn_id]");
			return;
		}

		if (spawn_id == 0) {
			c->Message(Chat::White, "Invalid spawn ID. Usage: #goto id [spawn_id]");
			return;
		}

		// Look up the mob by spawn ID
		Mob* target_mob = entity_list.GetMobID(spawn_id);
		if (!target_mob) {
			c->Message(Chat::White, "Spawn ID %u could not be found in this zone.", spawn_id);
			return;
		}

		// Teleport to the mob's location
		c->MovePC(
			zone->GetZoneID(),
			zone->GetInstanceID(),
			target_mob->GetX(),
			target_mob->GetY(),
			target_mob->GetZ(),
			target_mob->GetHeading()
		);

		c->Message(
			Chat::White,
			fmt::format(
				"Going to {} (ID: {}) in the same zone.",
				target_mob->GetName(),
				spawn_id
			).c_str()
		);
	}
	else if (goto_player) {
		const std::string& name = sep->arg[1];
		Client* t = entity_list.GetClientByName(name.c_str());
		if (t) {
			c->MovePC(
				zone->GetZoneID(),
				zone->GetInstanceID(),
				t->GetX(),
				t->GetY(),
				t->GetZ(),
				t->GetHeading()
			);

			c->Message(
				Chat::White,
				fmt::format(
					"Going to player {} in the same zone.",
					name
				).c_str()
			);
		}
		else if (c->GotoPlayer(name)) {
			c->Message(
				Chat::White,
				fmt::format(
					"Going to player {} in a different zone.",
					name
				).c_str()
			);
		}
		else {
			c->Message(
				Chat::White,
				fmt::format(
					"Player {} could not be found.",
					name
				).c_str()
			);
		}
	}
	else if (goto_position) {
		const glm::vec4& position = glm::vec4(
			Strings::ToFloat(sep->arg[1]),
			Strings::ToFloat(sep->arg[2]),
			Strings::ToFloat(sep->arg[3]),
			sep->arg[4] && Strings::IsFloat(sep->arg[4]) ? Strings::ToFloat(sep->arg[4]) : c->GetHeading()
		);
		c->MovePC(
			zone->GetZoneID(),
			zone->GetInstanceID(),
			position.x,
			position.y,
			position.z,
			position.w
		);
	}
	else if (goto_target) {
		Mob* t = c->GetTarget();

		c->MovePC(
			zone->GetZoneID(),
			zone->GetInstanceID(),
			t->GetX(),
			t->GetY(),
			t->GetZ(),
			t->GetHeading()
		);

		c->Message(
			Chat::White,
			fmt::format(
				"Going to {} in the same zone.",
				c->GetTargetDescription(t)
			).c_str()
		);
	}
}
