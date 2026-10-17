#include <chrono>
#include <memory>
#include <vector>
#include <thread>
#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
#include "turtlesim/srv/set_pen.hpp"

using namespace std::chrono_literals;

struct Point {
    float x;
    float y;
};

class KonohaTeleportVisualizer : public rclcpp::Node {
public:
    KonohaTeleportVisualizer() : Node("konoha_teleport_node") {
        teleport_client_ = this->create_client<turtlesim::srv::TeleportAbsolute>("/turtle1/teleport_absolute");
        pen_client_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");

        teleport_client_->wait_for_service();
        pen_client_->wait_for_service();
    }


    void drawKonohaLogo() {

        static const std::vector<Point> outerAndSpiralPath = {
            {9.500f, 8.887f}, {9.379f, 8.792f}, {9.209f, 8.622f}, {9.095f, 8.508f}, {8.982f, 8.395f}, {8.811f, 8.225f},
            {8.690f, 8.130f}, {8.577f, 8.017f}, {8.406f, 7.847f}, {8.262f, 7.808f}, {8.109f, 7.797f}, {7.892f, 7.855f},
            {7.755f, 7.911f}, {7.612f, 7.953f}, {7.394f, 8.007f}, {7.255f, 8.060f}, {7.106f, 8.087f}, {6.887f, 8.140f},
            {6.738f, 8.167f}, {6.588f, 8.193f}, {6.359f, 8.220f}, {6.198f, 8.220f}, {6.038f, 8.220f}, {5.808f, 8.247f},
            {5.659f, 8.220f}, {5.498f, 8.220f}, {5.268f, 8.193f}, {5.113f, 8.180f}, {4.970f, 8.140f}, {4.751f, 8.087f},
            {4.607f, 8.047f}, {4.470f, 7.990f}, {4.267f, 7.900f}, {4.132f, 7.838f}, {4.001f, 7.767f}, {3.816f, 7.633f},
            {3.696f, 7.536f}, {3.574f, 7.441f}, {3.396f, 7.290f}, {3.302f, 7.168f}, {3.207f, 7.047f}, {3.073f, 6.862f},
            {2.993f, 6.734f}, {2.923f, 6.603f}, {2.809f, 6.409f}, {2.753f, 6.272f}, {2.714f, 6.128f}, {2.639f, 5.919f},
            {2.593f, 5.777f}, {2.567f, 5.627f}, {2.540f, 5.398f}, {2.513f, 5.248f}, {2.487f, 5.099f}, {2.460f, 4.869f},
            {2.391f, 4.737f}, {2.262f, 4.662f}, {2.121f, 4.495f}, {2.083f, 4.350f}, {2.033f, 4.210f}, {1.969f, 3.996f},
            {1.927f, 3.853f}, {1.874f, 3.714f}, {1.820f, 3.496f}, {1.767f, 3.358f}, {1.722f, 3.216f}, {1.660f, 3.001f},
            {1.607f, 2.863f}, {1.570f, 2.717f}, {1.527f, 2.495f}, {1.500f, 2.345f}, {1.506f, 2.187f}, {1.727f, 2.140f},
            {1.888f, 2.140f}, {2.048f, 2.140f}, {2.278f, 2.113f}, {2.438f, 2.113f}, {2.599f, 2.113f}, {2.840f, 2.113f},
            {3.000f, 2.113f}, {3.160f, 2.113f}, {3.401f, 2.113f}, {3.562f, 2.113f}, {3.722f, 2.113f}, {3.963f, 2.113f},
            {4.089f, 2.196f}, {4.235f, 2.247f}, {4.465f, 2.220f}, {4.614f, 2.193f}, {4.775f, 2.193f}, {5.004f, 2.167f},
            {5.165f, 2.167f}, {5.406f, 2.167f}, {5.566f, 2.167f}, {5.715f, 2.193f}, {5.948f, 2.214f}, {6.100f, 2.233f},
            {6.244f, 2.273f}, {6.463f, 2.327f}, {6.607f, 2.367f}, {6.750f, 2.407f}, {6.947f, 2.513f}, {7.082f, 2.575f},
            {7.211f, 2.651f}, {7.389f, 2.802f}, {7.502f, 2.916f}, {7.616f, 3.029f}, {7.748f, 3.215f}, {7.843f, 3.336f},
            {7.919f, 3.465f}, {8.007f, 3.670f}, {8.060f, 3.808f}, {8.087f, 3.957f}, {8.140f, 4.176f}, {8.167f, 4.325f},
            {8.167f, 4.486f}, {8.193f, 4.716f}, {8.167f, 4.865f}, {8.140f, 5.014f}, {8.113f, 5.244f}, {8.087f, 5.393f},
            {8.033f, 5.532f}, {7.954f, 5.740f}, {7.900f, 5.878f}, {7.821f, 6.006f}, {7.689f, 6.191f}, {7.594f, 6.313f},
            {7.473f, 6.407f}, {7.295f, 6.559f}, {7.166f, 6.634f}, {7.032f, 6.700f}, {6.835f, 6.805f}, {6.690f, 6.843f},
            {6.548f, 6.887f}, {6.318f, 6.913f}, {6.169f, 6.940f}, {6.008f, 6.940f}, {5.779f, 6.913f}, {5.629f, 6.887f},
            {5.480f, 6.860f}, {5.269f, 6.789f}, {5.124f, 6.751f}, {4.995f, 6.675f}, {4.801f, 6.561f}, {4.680f, 6.467f},
            {4.567f, 6.369f}, {4.426f, 6.186f}, {4.351f, 6.057f}, {4.273f, 5.929f}, {4.180f, 5.727f}, {4.140f, 5.583f},
            {4.113f, 5.433f}, {4.113f, 5.193f}, {4.113f, 5.032f}, {4.140f, 4.883f}, {4.167f, 4.653f}, {4.220f, 4.515f},
            {4.276f, 4.377f}, {4.408f, 4.192f}, {4.522f, 4.078f}, {4.642f, 3.980f}, {4.837f, 3.870f}, {4.966f, 3.794f},
            {5.115f, 3.767f}, {5.345f, 3.740f}, {5.494f, 3.713f}, {5.655f, 3.713f}, {5.881f, 3.748f}, {6.026f, 3.786f},
            {6.161f, 3.847f}, {6.348f, 3.975f}, {6.443f, 4.096f}, {6.519f, 4.225f}, {6.593f, 4.435f}, {6.620f, 4.585f},
            {6.647f, 4.734f}, {6.620f, 4.964f}, {6.593f, 5.113f}, {6.546f, 5.254f}, {6.413f, 5.440f}, {6.300f, 5.553f},
        };

        static const std::vector<Point> tailDiagonalPath = {
            {2.487f, 4.727f}, {2.620f, 4.535f}, {2.647f, 4.382f}, {2.700f, 4.158f}, {2.747f, 4.013f}, {2.833f, 3.802f},
            {2.945f, 3.602f}, {3.024f, 3.470f}, {3.160f, 3.280f}, {3.258f, 3.156f}, {3.432f, 2.981f}, {3.614f, 2.826f},
            {3.746f, 2.747f}, {3.940f, 2.620f}, {4.033f, 2.502f}, {4.140f, 2.300f},
        };


        drawPathTeleport(outerAndSpiralPath);

        drawPathTeleport(tailDiagonalPath);

        setPen(0, 0, 0, 0, 1);
        teleport(1.0f, 1.0f, 0.0f);
    }

private:
    rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedPtr teleport_client_;
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr pen_client_;

    void setPen(uint8_t r, uint8_t g, uint8_t b, uint8_t width, uint8_t off) {
        auto req = std::make_shared<turtlesim::srv::SetPen::Request>();
        req->r = r;
        req->g = g;
        req->b = b;
        req->width = width;
        req->off = off;
        pen_client_->async_send_request(req);
        std::this_thread::sleep_for(100ms);
    }

    void teleport(float x, float y, float theta) {
        auto req = std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();
        req->x = x;
        req->y = y;
        req->theta = theta;
        teleport_client_->async_send_request(req);
        std::this_thread::sleep_for(20ms);
    }

    void drawPathTeleport(const std::vector<Point>& points) {
        if (points.empty()) return;

        setPen(255, 255, 255, 3, 1);
        teleport(points[0].x, points[0].y, 0.0f);
        setPen(255, 255, 255, 3, 0);
        for (size_t i = 1; i < points.size(); ++i) {
            teleport(points[i].x, points[i].y, 0.0f);
        }
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<KonohaTeleportVisualizer>();
    node->drawKonohaLogo();

    rclcpp::shutdown();
    return 0;
}
