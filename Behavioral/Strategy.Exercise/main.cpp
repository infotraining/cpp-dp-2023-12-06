#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <functional>

struct StatResult
{
    std::string description;
    double value;

    StatResult(const std::string& desc, double val)
        : description(desc)
        , value(val)
    {
    }
};

using Data = std::vector<double>;
using Results = std::vector<StatResult>;

// enum StatisticsType
// {
//     avg,
//     min_max,
//     sum
// };

class Statistics
{
public:
    virtual Results calculate(const Data& data) = 0;
    virtual ~Statistics() {};
};

namespace AlternativeTake
{
    using Strategy = std::function<void(const Data& data_, Results& results_)>;

    class Avg
    {
    public:
        void operator()(const Data& data_, Results& results_)
        {
            double sum = std::accumulate(data_.begin(), data_.end(), 0.0);
            double avg = sum / data_.size();

            StatResult result("Avg", avg);
            results_.push_back(result);
        }
    };

    class MinMax
    {
    public:
        void operator()(const Data& data_, Results& results_)
        {
            double min = *(std::min_element(data_.begin(), data_.end()));
            double max = *(std::max_element(data_.begin(), data_.end()));

            results_.emplace_back("Min", min);
            results_.emplace_back("Max", max);
        }
    };

    class Sum
    {
    public:
        void operator()(const Data& data_, Results& results_)
        {
            double sum = std::accumulate(data_.begin(), data_.end(), 0.0);

            results_.push_back(StatResult("Sum", sum));
        }
    };
}

class Avg : public Statistics
{
public:
    Results calculate(const Data& data) override
    {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        double avg = sum / data.size();

        return Results{ {"Avg", avg } };
    }
};

class MinMax : public Statistics
{
public:
    Results calculate(const Data& data) override
    {
        double min = *(std::min_element(data.begin(), data.end()));
        double max = *(std::max_element(data.begin(), data.end()));

        return Results{{ "Min", min },  {"Max", max}};
    }
};

class Sum : public Statistics
{
public:
    Results calculate(const Data& data) override
    {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);

        return { {"Sum", sum} };
    }
};

class DataAnalyzer
{
    Data data_;
    Results results_;
    std::shared_ptr<Statistics> stat_type_;

public:
    DataAnalyzer()
        : stat_type_{std::make_shared<Avg>()}
    {
    }

    DataAnalyzer(std::shared_ptr<Statistics> stat_type)
        : stat_type_{stat_type}
    {
    }

    void load_data(const std::string& file_name)
    {
        data_.clear();
        results_.clear();

        std::ifstream fin(file_name.c_str());
        if (!fin)
            throw std::runtime_error("File not opened");

        double d;
        while (fin >> d)
        {
            data_.push_back(d);
        }

        std::cout << "File " << file_name << " has been loaded...\n";
    }

    void set_statistics(std::shared_ptr<Statistics> stat_type)
    {
        stat_type_ = stat_type;
    }

    void calculate()
    {
        Results temp_result = stat_type_->calculate(data_); // delegation to strategy
        results_.insert(results_.end(), std::move_iterator(temp_result.begin()), std::move_iterator(temp_result.end()));
    }

    const Results& results() const
    {
        return results_;
    }
};

void show_results(const Results& results)
{
    for (const auto& rslt : results)
        std::cout << rslt.description << " = " << rslt.value << std::endl;
}

int main()
{
    auto avg = std::make_shared<Avg>();
    auto min_max = std::make_shared<MinMax>();
    auto sum = std::make_shared<Sum>();

    // auto std_stats = std::make_shared<StatGroup>();
    // std_stats->add(avg);
    // std_stats->add(min_max);
    // std_stats->add(sum);

    DataAnalyzer da{avg};
    da.load_data("stats_data.dat");
    da.calculate();

    show_results(da.results());

    std::cout << "\n\n";

    da.load_data("new_stats_data.dat");
    da.calculate();

    show_results(da.results());
}
