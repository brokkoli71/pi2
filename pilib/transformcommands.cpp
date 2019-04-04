
#include "transformcommands.h"
#include "commandmacros.h"

namespace pilib
{
	void addTransformCommands(vector<Command*>& commands)
	{
		commands.insert(commands.end(),
			{
			ADD_ALL(BinCommand),
			ADD_ALL(CropCommand),
			ADD_ALL(ScaleCommand),
			ADD_ALL(GenericTransformCommand),
			ADD_ALL(TranslateCommand)
			}
		);
	}

}
