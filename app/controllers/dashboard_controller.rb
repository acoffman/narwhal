class DashboardController < ApplicationController

  use_google_charts

def index
	overview
  render :overview
end

def edit_num
  @test_num = params[:value]
  render :text => @test_num
end

def overview
  @page_title = "Firewall Performance Overview"
  @test_num = params[:test_num]
  @test_num ||= 55
  @nav_over = "current"
  dataset3 = GoogleChartDataset.new :data => [0,100]
  dataset4 = GoogleChartDataset.new :data => [@test_num, @test_num], :color => 'FF0000', :title => 'Allowable Rate'
  dataset1 = GoogleChartDataset.new :data => [10, 20, 30, 40, 50]
  dataset2 = GoogleChartDataset.new :data => [10,50,4,10,16], :color => 'FF0000', :title => 'Traffic'
  @chart = init_chart(["Incoming Traffic", "Average Rates"], [dataset1, dataset2, dataset3, dataset4])
end

def ip
  @page_title = "IP Configuration"
  @nav_ip = "current"
  render :ip
end

def protocols
  @page_title = "Protocol Configuration"
  @nav_proto = "current"
  render :protocols
end

def rate
  @page_title = "Rate Limiting"
  @nav_rate = "current"
  render :rate
end

def move_item
  protocol = params[:protocol].split("_")[0]
  list = params[:protocol].split("_")[1]

  render :update do |page|
    page.remove "protocol_#{protocol}"
    page.insert_html :bottom, list, render(:partial=>"protocol", :object => protocol)
    page.visual_effect :highlight, "protocol_#{protocol}"
  end

end

private
  def init_chart(title, datasets)
    data = GoogleChartData.new :datasets => datasets
    axis = GoogleChartAxis.new :axis  => [GoogleChartAxis::LEFT, GoogleChartAxis::BOTTOM]
    chart = GoogleLineChart.new :chart_type => GoogleLineChart::XY , :width => 500, :height => 300, :title => title
    chart.data = data
    chart.axis = axis
    chart
  end

end
