// mvc.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

class IController {
 public:
     virtual ~IController() {}
     virtual void notify() = 0;
};

class model {
 public:
     std::string data() const { return str_; }
     void set_data(const std::string& str) { 
         str_ = str;

         if (controller_ != nullptr) {
             controller_->notify();
         }
     }
     void register_data_changed_handler(IController* controller) {
         controller_ = controller;
     }
 private:
  std::string str_;
  IController* controller_{nullptr};
};

class view {
public:
    void set_data(const std::string& str) {
        std::cout << "test:" << str.c_str() << std::endl;
    }
};

class Controller : public IController {
public:
    Controller(model& mod, view& view) {
        set_model(mod);
        set_view(view);
    }

    // from notify
    void notify() override {
        auto str = model_->data();

        if (view_)
            view_->set_data(str);
    }
private:
    void set_model(model& mod) {
        model_ = &mod;
        model_->register_data_changed_handler(this);
    }

    void set_view(view& view) {
        view_ = &view;
    }
private:
    model* model_{ nullptr };
    view* view_{ nullptr };
};

int main()
{
    std::cout << "Hello World!\n";

    model m;
    view v;
    Controller c(m, v);
    
    m.set_data("ttt");

    return 0;
}

