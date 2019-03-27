#include <iostream>

#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/auth/AWSAuthSigner.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>

void put_object(Aws::String key_name) {
    const Aws::String endpoint = "minio:9000";
    const Aws::String region = "";
    const Aws::String bucket_name = "hoge";

    auto input_data = Aws::MakeShared<Aws::StringStream>("");
    *input_data << "hoge!" << '\n';

    Aws::S3::Model::PutObjectRequest object_request;
    object_request.WithBucket(bucket_name)
                  .WithKey(key_name)
                  .SetBody(input_data);

    // マルチスレッドで動作させる場合にはここじゃだめ
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    std::cout << key_name << " InitAPI" << std::endl;
    //

    Aws::Auth::AWSCredentials cred = Aws::Auth::EnvironmentAWSCredentialsProvider().GetAWSCredentials();
    Aws::Client::ClientConfiguration clientConfig;
    if (!region.empty()) {
      clientConfig.region = region;
    }
    if (!endpoint.empty()) {
      clientConfig.scheme = Aws::Http::Scheme::HTTP;
      clientConfig.endpointOverride = endpoint;
    }
    auto const s3_client = Aws::S3::S3Client(cred, clientConfig,
      Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);

    auto const outcome = s3_client.PutObject(object_request);
    std::cout << key_name << " PutObject" << std::endl;
    if (outcome.IsSuccess()) {
      std::cout << key_name << " Done!" << std::endl;
    }
    else {
      std::cout << key_name << "Error: ";
      std::cout << outcome.GetError().GetMessage().c_str() << std::endl;
    }

    // マルチスレッドで動作させる場合にはここじゃだめ
    Aws::ShutdownAPI(options);
    std::cout << key_name << " ShutdownAPI" << std::endl;
    //
}

int main()
{
    // シングルスレッドで実行
    put_object("hoge1.txt");
    put_object("hoge2.txt");

    // マルチスレッドで実行
    // Aws::SDKOptions options;
    // Aws::InitAPI(options);

    // std::thread th_1(put_object, "hoge3.txt");
    // std::thread th_2(put_object, "hoge4.txt");
    // th_1.join();
    // th_2.join();

    // Aws::ShutdownAPI(options);

    return 0;
}