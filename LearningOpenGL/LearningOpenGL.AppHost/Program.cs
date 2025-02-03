var builder = DistributedApplication.CreateBuilder(args);

var apiService = builder.AddProject<Projects.LearningOpenGL_ApiService>("apiservice");

builder.AddProject<Projects.LearningOpenGL_Web>("webfrontend")
    .WithExternalHttpEndpoints()
    .WithReference(apiService);

builder.Build().Run();
