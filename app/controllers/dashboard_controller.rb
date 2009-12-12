class DashboardController < ApplicationController

  use_google_charts

def index
	overview
end

def overview
  @nav_over = "current"
  dataset1 = GoogleChartDataset.new :data => [10,50,4,10,16], :color => 'FF0000', :title => 'Java'
  dataset2 = GoogleChartDataset.new :data => [99, 81, 25, 54, 80], :color => '0000FF', :title => 'Ruby'
  data = GoogleChartData.new :datasets => [dataset1, dataset2]
  axis = GoogleChartAxis.new :axis  => [GoogleChartAxis::LEFT, GoogleChartAxis::BOTTOM,  GoogleChartAxis::RIGHT, GoogleChartAxis::BOTTOM]
  @chart = GoogleLineChart.new :width => 300, :height => 200, :title => ['Java vs. Ruby', 'Montly Job Opportunities']
  @chart.data = data
  @chart.axis = axis
  render :overview
end

def ip
  @nav_ip = "current"
  render :ip
end

def protocols
  @nav_proto = "current"
  render :protocols
end

def rate
  @nav_rate = "current"
  render :rate
end

end
