#include "ProfileMgr.h"
#include <BlackBone/src/BlackBone/Misc/Utils.h>

#define CURRENT_PROFILE L"\\FlorCodeCurrentProfile.xpr"

bool ProfileMgr::Save( const std::wstring& path /*= L""*/)
{
    try
    {
        auto filepath = path.empty() ? (blackbone::Utils::GetExeDirectory() + CURRENT_PROFILE) : path;

        acut::XmlDoc<wchar_t> xml;
        xml.create_document();

        for (auto& imgpath : _config.images)
            xml.append( L"FlorCodeConfig.imagePath" ).value( imgpath );

        xml.set( L"FlorCodeConfig.manualMapFlags", _config.mmapFlags );
        xml.set( L"FlorCodeConfig.procName",       _config.procName.c_str() );
        xml.set( L"FlorCodeConfig.hijack",         _config.hijack );
        xml.set( L"FlorCodeConfig.unlink",         _config.unlink );
        xml.set( L"FlorCodeConfig.erasePE",        _config.erasePE );
        xml.set( L"FlorCodeConfig.close",          _config.close );
        xml.set( L"FlorCodeConfig.krnHandle",      _config.krnHandle );
        xml.set( L"FlorCodeConfig.injIndef",       _config.injIndef );
        xml.set( L"FlorCodeConfig.processMode",    _config.processMode );
        xml.set( L"FlorCodeConfig.injectMode",     _config.injectMode );
        xml.set( L"FlorCodeConfig.delay",          _config.delay );
        xml.set( L"FlorCodeConfig.period",         _config.period );
        xml.set( L"FlorCodeConfig.skip",           _config.skipProc );
        xml.set( L"FlorCodeConfig.procCmdLine",    _config.procCmdLine.c_str() );
        xml.set( L"FlorCodeConfig.initRoutine",    _config.initRoutine.c_str() );
        xml.set( L"FlorCodeConfig.initArgs",       _config.initArgs.c_str() );

        xml.write_document( filepath );
        
        return true;
    }
    catch (const std::runtime_error&)
    {
        return false;
    }
}

bool ProfileMgr::Load( const std::wstring& path /*= L""*/ )
{
    try
    {
        auto filepath = path.empty() ? (blackbone::Utils::GetExeDirectory() + CURRENT_PROFILE) : path;
        if (!acut::file_exists( filepath ))
            return false;

        acut::XmlDoc<wchar_t> xml;
        xml.read_from_file( filepath );

        // Load images in a safe way
        if(xml.has( L"FlorCodeConfig.imagePath" ))
        {
            auto nodes = xml.all_nodes_named( L"FlorCodeConfig.imagePath" );
            for (auto& node : nodes)
                _config.images.emplace_back( node.value() );
        }

        xml.get_if_present( L"FlorCodeConfig.manualMapFlags",  _config.mmapFlags );
        xml.get_if_present( L"FlorCodeConfig.procName",        _config.procName );
        xml.get_if_present( L"FlorCodeConfig.hijack",          _config.hijack );
        xml.get_if_present( L"FlorCodeConfig.unlink",          _config.unlink );
        xml.get_if_present( L"FlorCodeConfig.erasePE",         _config.erasePE );
        xml.get_if_present( L"FlorCodeConfig.close",           _config.close );
        xml.get_if_present( L"FlorCodeConfig.krnHandle",       _config.krnHandle );
        xml.get_if_present( L"FlorCodeConfig.injIndef",        _config.injIndef );
        xml.get_if_present( L"FlorCodeConfig.processMode",     _config.processMode );
        xml.get_if_present( L"FlorCodeConfig.injectMode",      _config.injectMode );
        xml.get_if_present( L"FlorCodeConfig.delay",           _config.delay );
        xml.get_if_present( L"FlorCodeConfig.period",          _config.period );
        xml.get_if_present( L"FlorCodeConfig.skip",            _config.skipProc );
        xml.get_if_present( L"FlorCodeConfig.procCmdLine",     _config.procCmdLine );
        xml.get_if_present( L"FlorCodeConfig.initRoutine",     _config.initRoutine );
        xml.get_if_present( L"FlorCodeConfig.initArgs",        _config.initArgs );

        return true;
    }
    catch (const std::runtime_error&)
    {
        return false;
    }
}
