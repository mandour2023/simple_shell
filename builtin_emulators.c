#include "shell.h"

/**
 * _xexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _xexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _errtonum(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			display_err(info, "Illegal number: ");
			_epstr(info->argv[1]);
			_ech('\n');
			return (1);
		}
		info->err_num = _errtonum(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _xcd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _xcd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_view("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _takeenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _takeenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcomp(info->argv[1], "-") == 0)
	{
		if (!_takeenv(info, "OLDPWD="))
		{
			_view(s);
			_output('\n');
			return (1);
		}
		_view(_takeenv(info, "OLDPWD=")), _output('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _takeenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		display_err(info, "can't cd to ");
		_epstr(info->argv[1]), _ech('\n');
	}
	else
	{
		_h(info, "OLDPWD", _takeenv(info, "PWD="));
		_h(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _xhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _xhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_view("help call works. Function not yet implemented \n");
	if (0)
		_view(*arg_array); /* temp att_unused workaround */
	return (0);
}
