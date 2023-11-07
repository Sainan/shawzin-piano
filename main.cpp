#include <DigitalKeyboard.hpp>
#include <os.hpp>
#include <Process.hpp>
#include <Window.hpp>

using namespace soup;

int main()
{
	DigitalKeyboard keyboard;
	std::vector<Key> keys_down{};
	std::vector<Key> keys_to_press{};
	keys_down.reserve(3);
	keys_to_press.reserve(3);
	auto warframe_proc = Process::get("Warframe.x64.exe");
	while (true)
	{
		keyboard.update();

		if (warframe_proc && warframe_proc->id != Window::getFocused().getOwnerPid())
		{
			continue;
		}

		keys_to_press.clear();
		if (keyboard.keys[KEY_Z]) // C4
		{
			keys_to_press = { KEY_1 };
		}
		else if (keyboard.keys[KEY_S]) // C#4
		{
			keys_to_press = { KEY_SPACE, KEY_2 };
		}
		else if (keyboard.keys[KEY_X]) // D4
		{
			keys_to_press = { KEY_2 };
		}
		else if (keyboard.keys[KEY_C]) // E4
		{
			keys_to_press = { KEY_3 };
		}
		else if (keyboard.keys[KEY_V]) // F4
		{
			keys_to_press = { KEY_ARROW_LEFT, KEY_1 };
		}
		else if (keyboard.keys[KEY_G]) // F#4
		{
			keys_to_press = { KEY_SPACE, KEY_ARROW_LEFT, KEY_2 };
		}
		else if (keyboard.keys[KEY_B]) // G4
		{
			keys_to_press = { KEY_ARROW_LEFT, KEY_2 };
		}
		else if (keyboard.keys[KEY_H]) // G#4
		{
			keys_to_press = { KEY_SPACE, KEY_ARROW_LEFT, KEY_3 };
		}
		else if (keyboard.keys[KEY_N]) // A4
		{
			keys_to_press = { KEY_ARROW_LEFT, KEY_3 };
		}
		else if (keyboard.keys[KEY_J]) // A#4
		{
			keys_to_press = { KEY_SPACE, KEY_ARROW_DOWN, KEY_1 };
		}
		else if (keyboard.keys[KEY_M]) // B4
		{
			keys_to_press = { KEY_ARROW_DOWN, KEY_1 };
		}
		else if (keyboard.keys[KEY_COMMA]) // C5
		{
			keys_to_press = { KEY_ARROW_DOWN, KEY_2 };
		}
		else if (keyboard.keys[KEY_L]) // C#5
		{
			keys_to_press = { KEY_SPACE, KEY_ARROW_DOWN, KEY_3 };
		}
		else if (keyboard.keys[KEY_PERIOD]) // D5
		{
			keys_to_press = { KEY_ARROW_DOWN, KEY_3 };
		}
		else if (keyboard.keys[KEY_SEMICOLON]) // D#5
		{
			keys_to_press = { KEY_SPACE, KEY_ARROW_RIGHT, KEY_1 };
		}
		else if (keyboard.keys[KEY_SLASH]) // E5
		{
			keys_to_press = { KEY_ARROW_RIGHT, KEY_1 };
		}

		for (auto& ktp : keys_to_press)
		{
			if (std::find(keys_down.begin(), keys_down.end(), ktp) == keys_down.end())
			{
				os::simulateKeyDown(ktp);
				keys_down.emplace_back(ktp);
			}
		}
		for (auto i = keys_down.begin(); i != keys_down.end(); )
		{
			if (std::find(keys_to_press.begin(), keys_to_press.end(), *i) == keys_to_press.end())
			{
				os::simulateKeyRelease(*i);
				i = keys_down.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
}
