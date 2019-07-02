namespace server
{
    class movieServer{
        public:
        movieServer();
        ~movieServer();
        int listen (int fd);
    };
} // namespace movieServer
