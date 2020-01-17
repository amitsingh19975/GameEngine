#if !defined(dk_ENTRY_POINT_HPP)
#define dk_ENTRY_POINT_HPP

extern std::unique_ptr<dk::Dark> dk::CreateApplication();


int main(int argc, char** argv){
    (void)argc;
    (void)argv;
    dk::detail::Log::Init();
    dk::CoreLog::Info("Dark initialized!");
    auto app = dk::CreateApplication();
    Deref(app).Run();
    return 0;
}

#endif // dk_ENTRY_POINT_HPP
